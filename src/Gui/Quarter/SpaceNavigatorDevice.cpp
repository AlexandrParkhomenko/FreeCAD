/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#include <Quarter/devices/SpaceNavigatorDevice.h>

#include <QApplication>
#include <QWidget>
#include <QtCore/QEvent>

#include <Inventor/events/SoEvent.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

#include "NativeEvent.h"

#include <cstdio>


namespace SIM { namespace Coin3D { namespace Quarter {
class SpaceNavigatorDeviceP {
public:
  SpaceNavigatorDeviceP(SpaceNavigatorDevice * master) {
    this->master = master;
    this->hasdevice = false;
    this->windowid = 0;
    this->motionevent = new SoMotion3Event;
    this->buttonevent = new SoSpaceballButtonEvent;
  }
  ~SpaceNavigatorDeviceP() {
    delete this->motionevent;
    delete this->buttonevent;
  }

  static bool customEventFilter(void * message, long * result);

  SpaceNavigatorDevice * master;
  bool hasdevice;
  WId windowid;

  SoMotion3Event * motionevent;
  SoSpaceballButtonEvent * buttonevent;

};
}}}


#define PRIVATE(obj) obj->pimpl
using namespace SIM::Coin3D::Quarter;

SpaceNavigatorDevice::SpaceNavigatorDevice()
{
  PRIVATE(this) = new SpaceNavigatorDeviceP(this);
}

SpaceNavigatorDevice::SpaceNavigatorDevice(QuarterWidget *quarter) :
    InputDevice(quarter)
{
    PRIVATE(this) = new SpaceNavigatorDeviceP(this);
}

SpaceNavigatorDevice::~SpaceNavigatorDevice()
{
  delete PRIVATE(this);
}


const SoEvent *
SpaceNavigatorDevice::translateEvent(QEvent * event)
{
  Q_UNUSED(event); 
  SoEvent * ret = NULL;
  return ret;
}


#undef PRIVATE
#undef PUBLIC

