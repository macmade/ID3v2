/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      ID3v2.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 main header file
 */

#ifndef ID3V2
#define ID3V2

#include <string>
#include <iostream>
#include <vector>
#include <cstdint>

/*******************************************************************************
 * Base
 ******************************************************************************/

#include <ID3v2/ID3v2-Version.h>
#include <ID3v2/ID3v2-AbstractFrame.h>
#include <ID3v2/ID3v2-TextFrame.h>
#include <ID3v2/ID3v2-ExtendedHeader.h>
#include <ID3v2/ID3v2-Tag.h>
#include <ID3v2/Frame/ID3v2-Frame-Unknown.h>

/*******************************************************************************
 * Frames - v2.2.0
 ******************************************************************************/

#include <ID3v2/Frame/v22/ID3v2-Frame-BUF.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-CNT.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-COM.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-CRA.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-CRM.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-EQU.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-ETC.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-GEO.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-IPL.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-LNK.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-MCI.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-MLL.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-PIC.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-POP.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-REV.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-RVA.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-SLT.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-STC.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TAL.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TBP.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TCM.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TCO.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TCR.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TDA.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TDY.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TEN.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TFT.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TIM.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TKE.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TLA.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TLE.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TMT.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TOA.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TOF.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TOL.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TOR.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TOT.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TP1.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TP2.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TP3.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TP4.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TPA.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TPB.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TRC.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TRD.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TRK.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TSI.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TSS.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TT1.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TT2.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TT3.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TXT.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TXX.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-TYE.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-UFI.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-ULT.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-WAF.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-WAR.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-WAS.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-WCM.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-WCP.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-WPB.h>
#include <ID3v2/Frame/v22/ID3v2-Frame-WXX.h>

/*******************************************************************************
 * Frames - v2.3.0
 ******************************************************************************/

#include <ID3v2/Frame/v23/ID3v2-Frame-AENC.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-APIC.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-COMM.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-COMR.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-ENCR.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-EQUA.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-ETCO.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-GEOB.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-GRID.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-IPLS.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-LINK.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-MCDI.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-MLLT.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-OWNE.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-PCNT.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-POPM.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-POSS.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-PRIV.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-RBUF.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-RVAD.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-RVRB.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-SYLT.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-SYTC.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TALB.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TBPM.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TCOM.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TCON.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TCOP.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TDAT.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TDLY.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TENC.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TEXT.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TFLT.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TIME.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TIT1.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TIT2.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TIT3.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TKEY.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TLAN.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TLEN.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TMED.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TOAL.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TOFN.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TOLY.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TOPE.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TORY.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TOWN.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TPE1.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TPE2.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TPE3.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TPE4.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TPOS.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TPUB.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TRCK.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TRDA.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TRSN.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TRSO.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TSIZ.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TSRC.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TSSE.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TXXX.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-TYER.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-UFID.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-USER.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-USLT.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-WCOM.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-WCOP.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-WOAF.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-WOAR.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-WOAS.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-WORS.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-WPAY.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-WPUB.h>
#include <ID3v2/Frame/v23/ID3v2-Frame-WXXX.h>

#endif /* ID3V2 */
