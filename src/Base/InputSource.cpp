/***************************************************************************
 *   Copyright (c) Riegel         <juergen.riegel@web.de>                  *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <xercesc/sax/SAXParseException.hpp>
# include <xercesc/sax/SAXException.hpp>
# include <xercesc/sax2/XMLReaderFactory.hpp>

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLExceptMsgs.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>

/// Here the FreeCAD includes sorted by Base,App,Gui......
#include "InputSource.h"
#include "Exception.h"
#include "XMLTools.h"

XERCES_CPP_NAMESPACE_USE

using namespace Base;
using namespace std;


// ---------------------------------------------------------------------------
//  StdInputStream: Constructors and Destructor
// ---------------------------------------------------------------------------
StdInputStream::StdInputStream( std::istream& Stream, XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* const manager ) 
  : stream(Stream), fMemoryManager(manager)
{
    state.flags |= QTextCodec::IgnoreHeader;
    state.flags |= QTextCodec::ConvertInvalidToNull;
}


StdInputStream::~StdInputStream()
{
}


// ---------------------------------------------------------------------------
//  StdInputStream: Implementation of the input stream interface
// ---------------------------------------------------------------------------
#if (XERCES_VERSION_MAJOR == 2)
unsigned int StdInputStream::curPos() const
{
  return stream.tellg();
}

unsigned int StdInputStream::readBytes( XMLByte* const  toFill, const unsigned int maxToRead )
{
  //
  //  Read up to the maximum bytes requested. We return the number
  //  actually read.
  //
  
  stream.read((char *)toFill,maxToRead);
  XMLSize_t len = stream.gcount();

  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  const QString text = codec->toUnicode((char *)toFill, len, &state);
  if (state.invalidChars > 0) {
      // In case invalid characters were found decode back to 'utf-8' and replace
      // them with '?'
      // First, Qt replaces invalid characters with '\0' (see ConvertInvalidToNull)
      // but Xerces doesn't like this because it handles this as termination. Thus,
      // we have to go through the array and replace '\0' with '?'.
      XMLSize_t pos = 0;
      QByteArray ba = codec->fromUnicode(text);
      for (int i=0; i<ba.length(); i++, pos++) {
          if (pos < len && ba[i] == '\0')
              toFill[i] = '?';
      }
  }

  return len;
}
#else
XMLFilePos StdInputStream::curPos() const
{
  return stream.tellg();
}

XMLSize_t StdInputStream::readBytes( XMLByte* const  toFill, const XMLSize_t maxToRead )
{
  //
  //  Read up to the maximum bytes requested. We return the number
  //  actually read.
  //
  
  stream.read((char *)toFill,maxToRead);
  XMLSize_t len = stream.gcount();

  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  const QString text = codec->toUnicode((char *)toFill, len, &state);
  if (state.invalidChars > 0) {
      // In case invalid characters were found decode back to 'utf-8' and replace
      // them with '?'
      // First, Qt replaces invalid characters with '\0' (see ConvertInvalidToNull)
      // but Xerces doesn't like this because it handles this as termination. Thus,
      // we have to go through the array and replace '\0' with '?'.
      XMLSize_t pos = 0;
      QByteArray ba = codec->fromUnicode(text);
      for (int i=0; i<ba.length(); i++, pos++) {
          if (pos < len && ba[i] == '\0')
              toFill[i] = '?';
      }
  }

  return len;
}
#endif


// ---------------------------------------------------------------------------
//  StdInputSource: Constructors and Destructor
// ---------------------------------------------------------------------------
StdInputSource::StdInputSource ( std::istream& Stream, const char* filePath, XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* const manager )
  : InputSource(manager),stream(Stream)
{
  // we have to set the file name in case an error occurs
  XStr tmpBuf(filePath);
  setSystemId(tmpBuf.unicodeForm());
}


StdInputSource::~StdInputSource()
{
}


// ---------------------------------------------------------------------------
//  StdInputSource: InputSource interface implementation
// ---------------------------------------------------------------------------
BinInputStream* StdInputSource::makeStream() const
{
  StdInputStream* retStrm = new StdInputStream(stream /*, getMemoryManager()*/);
  return retStrm;
}

