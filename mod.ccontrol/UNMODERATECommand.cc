/**
 * UNMODERATECommand.cc
 * Cause the bot to unmoderate a  channel
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 *
 * $Id: UNMODERATECommand.cc,v 1.14 2006/09/26 17:36:01 kewlio Exp $
 */

#include	<string>

#include	"ccontrol.h"
#include	"CControlCommands.h"
#include	"StringTokenizer.h"
#include	"Network.h"
#include	"Constants.h"
#include	"ccBadChannel.h"
#include	"gnuworld_config.h"

RCSTAG( "$Id: UNMODERATECommand.cc,v 1.14 2006/09/26 17:36:01 kewlio Exp $" ) ;

namespace gnuworld
{

using std::string ;

namespace uworld
{

bool UNMODERATECommand::Exec( iClient* theClient, const string& Message )
{
StringTokenizer st( Message ) ;
if( st.size() < 2 )
	{
	Usage( theClient ) ;
	return true ;
	}
if(st[1].size() > channel::MaxName)
	{
	bot->Notice(theClient,"Channel name can't be more than %d characters",
		channel::MaxName);
	}

bot->MsgChanLog("UNMODERATE %s\n",st.assemble(1).c_str());

ccBadChannel* Chan = bot->isBadChannel(st[1]);
if(Chan)
        {
        bot->Notice(theClient,"Sorry, but you can't change modes in "
                             "this channel because: %s",
                             Chan->getReason().c_str());
        return false;
        }

Channel* theChan = Network->findChannel( st[ 1 ] ) ;
if( NULL == theChan )
	{
	bot->Notice( theClient, "Unable to find channel %s\n",
		st[ 1 ].c_str() ) ;
	return true ;
	}

if(!theChan->getMode(Channel::MODE_M))
	{
	bot->Notice( theClient,"Channel %s is not moderated",
		st[ 1 ].c_str());
	return false;
	}

bot->Mode( theChan, "-m", string(), true );

return true ;

}
}
}
