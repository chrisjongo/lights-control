//-----------------------------------------------------------------------------
//
//      zwave.h
//
//      Cli/C++ wrapper for the C++ OpenZWave Manager class
//
//      Copyright (c) 2010 Amer Harb <harb_amer@hotmail.com>
//
//      SOFTWARE NOTICE AND LICENSE
//
//      This file is part of OpenZWave.
//
//      OpenZWave is free software: you can redistribute it and/or modify
//      it under the terms of the GNU Lesser General Public License as published
//      by the Free Software Foundation, either version 3 of the License,
//      or (at your option) any later version.
//
//      OpenZWave is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU Lesser General Public License for more details.
//
//      You should have received a copy of the GNU Lesser General Public License
//      along with OpenZWave.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------


#pragma once
#include "Windows.h"
#include "Manager.h"
#include "Value.h"
#include "ValueStore.h"
#include "ValueID.h"
#include "ValueBool.h"
#include "ValueInt.h"
#include "ValueByte.h"
#include "ValueString.h"
#include "ValueShort.h"
#include "ValueDecimal.h"
#include "Notification.h"
#include "stdio.h"

#include <msclr/auto_gcroot.h>
#include <msclr/lock.h>

using namespace System;
using namespace System::Threading;
using namespace System::Collections::Generic;
using namespace OpenZWave;
using namespace Runtime::InteropServices;

namespace OpenZWaveDotNet
{
	public ref class ZWNotification
	{
	public:
		enum class Type
		{
			ValueAdded						= Notification::Type_ValueAdded,	
			ValueRemoved					= Notification::Type_ValueRemoved,		
			ValueChanged					= Notification::Type_ValueChanged,		
			ValueRefreshed					= Notification::Type_ValueRefreshed,
			Group							= Notification::Type_Group,				
			NodeNew							= Notification::Type_NodeNew,
			NodeAdded						= Notification::Type_NodeAdded,			
			NodeRemoved						= Notification::Type_NodeRemoved,		
			NodeProtocolInfo				= Notification::Type_NodeProtocolInfo,
			NodeNaming						= Notification::Type_NodeNaming,
			NodeEvent						= Notification::Type_NodeEvent,
			PollingDisabled					= Notification::Type_PollingDisabled,	
			PollingEnabled					= Notification::Type_PollingEnabled,	
			SceneEvent						= Notification::Type_SceneEvent,
			CreateButton					= Notification::Type_CreateButton,
			DeleteButton					= Notification::Type_DeleteButton,
			ButtonOn						= Notification::Type_ButtonOn,
			ButtonOff						= Notification::Type_ButtonOff,
			DriverReady						= Notification::Type_DriverReady,		
			DriverFailed					= Notification::Type_DriverFailed,
			DriverReset						= Notification::Type_DriverReset,
			EssentialNodeQueriesComplete	= Notification::Type_EssentialNodeQueriesComplete,
			NodeQueriesComplete				= Notification::Type_NodeQueriesComplete,
			AwakeNodesQueried				= Notification::Type_AwakeNodesQueried,
			AllNodesQueried					= Notification::Type_AllNodesQueried,
			Notification					= Notification::Type_Notification
		};

		ZWNotification( Notification* notification )
		{
			m_type = (Type)Enum::ToObject( Type::typeid, notification->GetType() );
			m_byte = notification->GetByte();
			m_valueId = gcnew ZWValueID( notification->GetValueID() );
		}

		Type GetType(){ return m_type; }
		uint32 GetHomeId(){ return m_valueId->GetHomeId(); }
		uint8 GetNodeId(){ return m_valueId->GetNodeId(); }
		ZWValueID^ GetValueID(){ return m_valueId; }
		uint8 GetGroupIdx(){ assert(Type::Group==m_type); return m_byte; } 
		uint8 GetEvent(){ assert(Type::NodeEvent==m_type); return m_byte; }
		uint8 GetByte(){ return m_byte; }

	internal:
		Type		m_type;
		ZWValueID^	m_valueId;
		uint8		m_byte;
	};
}