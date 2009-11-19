/*****************************************************************************
 * GenericEffect.cpp: Abstract class you must inherit from, when you program
 * an effect module
 *****************************************************************************
 * Copyright (C) 2008-2009 the VLMC team
 *
 * Authors: Vincent Carrubba <cyberbouba@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include "GenericEffect.h"

GenericEffect::GenericEffect(IEffectPlugin* plugin) : m_plugin(plugin), m_videoInputs(NULL), m_videoOutputs(NULL)
{
    m_plugin->init(this);
}

GenericEffect::~GenericEffect()
{
    delete m_plugin;
    if ( m_videoInputs )
        delete [] m_videoInputs;
    if ( m_videoOutputs )
        delete [] m_videoOutputs;
}


//-------------------------------------------------------------------
//
// DEPRECATED
//
//

void                                    GenericEffect::init( quint32 const nbvideoinputs,
                                                             quint32 const nbvideooutputs )
{
    m_videoInputs = new InSlot<LightVideoFrame>[nbvideoinputs];
    m_videoOutputs = new OutSlot<LightVideoFrame>[nbvideooutputs];
    return ;
}

void                                    GenericEffect::render( void )
{
    m_plugin->render();
    return ;
}

IEffectPlugin*                          GenericEffect::getInternalPlugin( void )
{
    return ( m_plugin );
}

InSlot<LightVideoFrame> &               GenericEffect::getVideoInput(quint32 id)
{
    return ( m_videoInputs[id] );
}

OutSlot<LightVideoFrame> &              GenericEffect::getVideoOutput(quint32 id)
{
    return ( m_videoOutputs[id] );
}


//-------------------------------------------------------------------
//
// DEPRECATED
//
//

// CONNECTIONS BETWEEN GENERICEFFECTS

void				GenericEffect::connectOutput( quint32 outIndex, GenericEffect* destEffect, quint32 inIndex)
{
  // THINK TO CHECK IF THE SLOTS EXISTS BY CALLING THE PRIVATES METHODS!!!
  ( m_videoOutputs[outIndex] ).connect( destEffect->m_videoInputs[inIndex] );
  return ;
}

// CONNECTIONS DETWEEN GENERICEFFECT & OUTSLOT/INSLOT

void				GenericEffect::connect( OutSlot<LightVideoFrame> & out, quint32 inIndex )
{
  out.connect( m_videoInputs[inIndex] );
  return ;
}

void				GenericEffect::connect( quint32 outIndex, InSlot<LightVideoFrame> & in )
{
  ( m_videoOutputs[outIndex] ).connect( in );
  return ;
}
