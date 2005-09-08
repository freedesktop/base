/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ScrollHelper.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 15:34:10 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef DBAUI_SCROLLHELPER_HXX
#define DBAUI_SCROLLHELPER_HXX

#ifndef _LINK_HXX 
#include <tools/link.hxx>
#endif
#ifndef _SV_GEN_HXX 
#include <tools/gen.hxx>
#endif
#ifndef _SV_TIMER_HXX 
#include <vcl/timer.hxx>
#endif

namespace dbaui
{
    class OScrollHelper
    {
        Link	m_aUpScroll;
        Link	m_aDownScroll;
    public:
        /** default contructor
        */
        OScrollHelper();

        ~OScrollHelper();

        /** set the memthod which should be called when scrolling up
            @param	_rUpScroll
                the method to set
        */
        inline void setUpScrollMethod( const Link& _rUpScroll )
        {
            m_aUpScroll = _rUpScroll;
        }

        /** set the memthod which should be called when scrolling down
            @param	_rDownScroll
                the method to set
        */
        inline void setDownScrollMethod( const Link& _rDownScroll )
        {
            m_aDownScroll = _rDownScroll;
        }

        /** check if a scroll method has to be called
            @param	_rPoint	
                the current selection point
            @param	_rOutputSize
                the output size of the window
        */
        void scroll(const Point& _rPoint, const Size& _rOutputSize);
    };
}
#endif // DBAUI_SCROLLHELPER_HXX

