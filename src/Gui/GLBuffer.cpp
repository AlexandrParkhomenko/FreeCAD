/***************************************************************************
 *   Copyright (c) 2018 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#ifndef FC_OS_WIN32
#define GL_GLEXT_PROTOTYPES
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/misc/SoContextHandler.h>

#include <string>

#include "GLBuffer.h"

using namespace Gui;


OpenGLBuffer::OpenGLBuffer(GLenum type)
  : target(type)
  , bufferId(0)
  , context(-1)
  , currentContext(-1)
  , glue(0)
{
    SoContextHandler::addContextDestructionCallback(context_destruction_cb, this);
}

OpenGLBuffer::~OpenGLBuffer()
{
    SoContextHandler::removeContextDestructionCallback(context_destruction_cb, this);

    destroy();
}

/*!
 * \brief OpenGLBuffer::isVBOSupported returns if the OpenGL driver
 * supports the VBO extension.
 * When calling this function there must be a current OpenGL context.
 * \return
 */
bool OpenGLBuffer::isVBOSupported(uint32_t ctx)
{
    auto glue = cc_glglue_instance(ctx);
    if (!glue || !cc_glglue_has_vertex_buffer_object(glue))
        return false;
    const GLubyte * str = glGetString(GL_EXTENSIONS);
    if (!str)
        return false;
    std::string ext = reinterpret_cast<const char*>(str);
    return (ext.find("GL_ARB_vertex_buffer_object") != std::string::npos);
}

void OpenGLBuffer::setCurrentContext(uint32_t ctx)
{
    currentContext = ctx;
    glue = cc_glglue_instance(currentContext);
}

bool OpenGLBuffer::create()
{
    if (bufferId > 0)
        return true;

    if (!cc_glglue_has_vertex_buffer_object(glue))
        return false;

    cc_glglue_glGenBuffers(glue, 1, &bufferId);
    context = currentContext;
    return true;
}

bool OpenGLBuffer::isCreated() const
{
    return (bufferId > 0);
}

void OpenGLBuffer::destroy()
{
    // schedule delete for all allocated GL resources
    if (bufferId > 0) {
        void * ptr0 = (void*) ((uintptr_t) bufferId);
        SoGLCacheContextElement::scheduleDeleteCallback(context, buffer_delete, ptr0);
        bufferId = 0;
    }
}

void OpenGLBuffer::allocate(const void *data, int count)
{
    if (bufferId > 0) {
        cc_glglue_glBufferData(glue, target, count, data, GL_STATIC_DRAW);
    }
}

bool OpenGLBuffer::bind()
{
    if (bufferId) {
        if (context != currentContext) {
            SoDebugError::postWarning("OpenGLBuffer::bind",
                                      "buffer not created");
            return false;
        }

        cc_glglue_glBindBuffer(glue, target, bufferId);
        return true;
    }
    return false;
}

void OpenGLBuffer::release()
{
    if (bufferId) {
        cc_glglue_glBindBuffer(glue, target, 0);
    }
}

GLuint OpenGLBuffer::getBufferId() const
{
    return bufferId;
}

uint32_t OpenGLBuffer::getBoundContext() const
{
    return context;
}

int OpenGLBuffer::size() const
{
    GLint value = -1;
    if (bufferId > 0) {
        cc_glglue_glGetBufferParameteriv(glue, target, GL_BUFFER_SIZE, &value);
    }
    return value;
}

void OpenGLBuffer::context_destruction_cb(uint32_t context, void * userdata)
{
    OpenGLBuffer * self = static_cast<OpenGLBuffer*>(userdata);

    if (self->context == context && self->bufferId) {
        const cc_glglue * glue = cc_glglue_instance((int) context);
        GLuint buffer = self->bufferId;
        cc_glglue_glDeleteBuffers(glue, 1, &buffer);
        self->context = -1;
        self->bufferId = 0;
    }
}

void OpenGLBuffer::buffer_delete(void * closure, uint32_t contextid)
{
    const cc_glglue * glue = cc_glglue_instance((int) contextid);
    GLuint id = (GLuint) ((uintptr_t) closure);
    cc_glglue_glDeleteBuffers(glue, 1, &id);
}
