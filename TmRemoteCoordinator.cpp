/*
    This file is part of the Zero Reserve Plugin for Retroshare.

    Zero Reserve is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Zero Reserve is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Zero Reserve.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "TmRemoteCoordinator.h"
#include "RSZRRemoteItems.h"
#include "Router.h"
#include "ZeroReservePlugin.h"
#include "p3ZeroReserverRS.h"
#include "Payment.h"

TmRemoteCoordinator::TmRemoteCoordinator(const ZR::VirtualAddress & addr , Payment *payment) :
    TransactionManager( addr ),
    m_Destination( addr ),
    m_Payment( payment )
{
}

TmRemoteCoordinator::~TmRemoteCoordinator()
{
    delete m_Payment;
}

ZR::RetVal TmRemoteCoordinator::init()
{
    std::cerr << "Zero Reserve: Setting TX manager up as coordinator" << std::endl;
    p3ZeroReserveRS * p3zr = static_cast< p3ZeroReserveRS* >( g_ZeroReservePlugin->rs_pqi_service() );
    RSZRRemoteTxItem * item = new RSZRRemoteTxItem( m_Destination, QUERY );
    ZR::PeerAddress addr = Router::Instance()->nextHop( m_Destination );
    if( addr.empty() )
        return ZR::ZR_FAILURE;
    item->PeerId( addr );
    p3zr->sendItem( item );
    return ZR::ZR_SUCCESS;
}


ZR::RetVal TmRemoteCoordinator::processItem( RSZRRemoteTxItem * item )
{

}

ZR::RetVal TmRemoteCoordinator::abortTx( RSZRRemoteTxItem *item )
{

}
