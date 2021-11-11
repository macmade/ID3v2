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
 * @header      ID3v2-AbstractFrame.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 abstract frame
 */

#include <ID3v2.h>
#include <ID3v2/ID3v2-PrivateTypes.h>
#include <sstream>

namespace ID3v2
{
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpadded"
    #endif
    
    class AbstractFrame::IMPL
    {
        public:
            
            static AbstractFrame * NewFrame( ID3v22Frame header, std::size_t size, uint8_t * data, Version version );
            static AbstractFrame * NewFrame( ID3v23Frame header, std::size_t size, uint8_t * data, Version version );
            
            IMPL( void );
            ~IMPL( void );
            
            ID3v22Frame  frame22;
            ID3v23Frame  frame23;
            std::size_t  frameSize;
            uint8_t    * data;
            Version      version;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
    
    AbstractFrame * AbstractFrame::NewFrameFromFileHandle( FILE * fh, Version version )
    {
        ID3v22Frame  frameHeader22;
        ID3v23Frame  frameHeader23;
        std::size_t  frameSize;
        char       * data;
        
        if( fh == NULL )
        {
            return NULL;
        }
        
        memset( &frameHeader22, 0, sizeof( ID3v22Frame ) );
        memset( &frameHeader23, 0, sizeof( ID3v23Frame ) );
        
        if( version < Version( 2, 3, 0 ) )
        {
            if( fread( &frameHeader22, 1, sizeof( ID3v22Frame ), fh ) != sizeof( ID3v22Frame ) )
            {
                goto error;
            }
            
            {
                std::size_t s1;
                std::size_t s2;
                std::size_t s3;
                
                s1   = static_cast< std::size_t >( frameHeader22.size[ 0 ] );
                s2   = static_cast< std::size_t >( frameHeader22.size[ 1 ] );
                s3   = static_cast< std::size_t >( frameHeader22.size[ 2 ] );
                s1  &= 0xFF;
                s2  &= 0xFF;
                s3  &= 0xFF;
                s1 <<= 16;
                s2 <<= 8;
                
                frameSize = s1 | s2 | s3;
            }
        }
        else
        {
            if( fread( &frameHeader23, 1, sizeof( ID3v23Frame ), fh ) != sizeof( ID3v23Frame ) )
            {
                goto error;
            }
            
            {
                std::size_t s1;
                std::size_t s2;
                std::size_t s3;
                std::size_t s4;
                
                s1   = static_cast< std::size_t >( frameHeader23.size[ 0 ] );
                s2   = static_cast< std::size_t >( frameHeader23.size[ 1 ] );
                s3   = static_cast< std::size_t >( frameHeader23.size[ 2 ] );
                s4   = static_cast< std::size_t >( frameHeader23.size[ 3 ] );
                s1  &= 0xFF;
                s2  &= 0xFF;
                s3  &= 0xFF;
                s4  &= 0xFF;
                s1 <<= 24;
                s2 <<= 16;
                s3 <<= 8;
                
                frameSize = s1 | s2 | s3 | s4;
            }
        }
        
        data = new char[ frameSize ];
        
        if( data == NULL )
        {
            goto error;
        }
        
        if( fread( data, 1, frameSize, fh ) != frameSize )
        {
            goto error;
        }
        
        if( version < Version( 2, 3, 0 ) )
        {
            return AbstractFrame::IMPL::NewFrame( frameHeader22, frameSize, reinterpret_cast< uint8_t * >( data ), version );
        }
        
        return AbstractFrame::IMPL::NewFrame( frameHeader23, frameSize, reinterpret_cast< uint8_t * >( data ), version );
        
        error:
        
        return NULL;
    }
    
    AbstractFrame::AbstractFrame( void ): impl( new IMPL )
    {}
    
    AbstractFrame::~AbstractFrame( void )
    {
        delete this->impl;
    }
    
    std::string AbstractFrame::GetName( void ) const
    {
        std::stringstream ss;
        
        if( this->impl->version < Version( 2, 3, 0 ) )
        {
            ss << this->impl->frame22.id[ 0 ];
            ss << this->impl->frame22.id[ 1 ];
            ss << this->impl->frame22.id[ 2 ];
        }
        else
        {
            ss << this->impl->frame23.id[ 0 ];
            ss << this->impl->frame23.id[ 1 ];
            ss << this->impl->frame23.id[ 2 ];
            ss << this->impl->frame23.id[ 3 ];
        }
        
        return ss.str();
    }
    
    std::size_t AbstractFrame::GetSize( void ) const
    {
        return this->impl->frameSize;
    }
    
    const uint8_t * AbstractFrame::GetData( void ) const
    {
        return this->impl->data;
    }
    
    unsigned short  AbstractFrame::GetFlags( void ) const
    {
        unsigned short f1;
        unsigned short f2;
        
        if( this->impl->version < Version( 2, 3, 0 ) )
        {
            
        }
        
        f1   = static_cast< unsigned short >( this->impl->frame23.flags[ 0 ] );
        f2   = static_cast< unsigned short >( this->impl->frame23.flags[ 1 ] );
        f1  &= 0xFF;
        f2  &= 0xFF;
        f1 <<= 8;
        
        return f1 | f2;
    }
    
    bool AbstractFrame::HasFlag( Flag flag ) const
    {
        unsigned short flags;
        
        flags = this->GetFlags();
        
        switch( flag )
        {
            case FlagTagAlterPreservation:  return ( flags & 0x8000 ) ? true : false;
            case FlagFileAlterPreservation: return ( flags & 0x4000 ) ? true : false;
            case FlagReadOnly:              return ( flags & 0x2000 ) ? true : false;
            case FlagCompression:           return ( flags & 0x0080 ) ? true : false;
            case FlagEncryption:            return ( flags & 0x0040 ) ? true : false;
            case FlagGroupingIdentity:      return ( flags & 0x0020 ) ? true : false;
        }

        return false;
    }
    
    AbstractFrame * AbstractFrame::IMPL::NewFrame( ID3v22Frame header, std::size_t size, uint8_t * data, Version version )
    {
        AbstractFrame   * frame;
        std::stringstream ss;
        std::string       name;
        
        ss << header.id[ 0 ];
        ss << header.id[ 1 ];
        ss << header.id[ 2 ];
        
        name = ss.str();
        
             if( name == "BUF" ) { frame = new Frame::v22::BUF(); }
        else if( name == "CNT" ) { frame = new Frame::v22::CNT(); }
        else if( name == "COM" ) { frame = new Frame::v22::COM(); }
        else if( name == "CRA" ) { frame = new Frame::v22::CRA(); }
        else if( name == "CRM" ) { frame = new Frame::v22::CRM(); }
        else if( name == "EQU" ) { frame = new Frame::v22::EQU(); }
        else if( name == "ETC" ) { frame = new Frame::v22::ETC(); }
        else if( name == "GEO" ) { frame = new Frame::v22::GEO(); }
        else if( name == "IPL" ) { frame = new Frame::v22::IPL(); }
        else if( name == "LNK" ) { frame = new Frame::v22::LNK(); }
        else if( name == "MCI" ) { frame = new Frame::v22::MCI(); }
        else if( name == "MLL" ) { frame = new Frame::v22::MLL(); }
        else if( name == "PIC" ) { frame = new Frame::v22::PIC(); }
        else if( name == "POP" ) { frame = new Frame::v22::POP(); }
        else if( name == "REV" ) { frame = new Frame::v22::REV(); }
        else if( name == "RVA" ) { frame = new Frame::v22::RVA(); }
        else if( name == "SLT" ) { frame = new Frame::v22::SLT(); }
        else if( name == "STC" ) { frame = new Frame::v22::STC(); }
        else if( name == "TAL" ) { frame = new Frame::v22::TAL(); }
        else if( name == "TBP" ) { frame = new Frame::v22::TBP(); }
        else if( name == "TCM" ) { frame = new Frame::v22::TCM(); }
        else if( name == "TCO" ) { frame = new Frame::v22::TCO(); }
        else if( name == "TCR" ) { frame = new Frame::v22::TCR(); }
        else if( name == "TDA" ) { frame = new Frame::v22::TDA(); }
        else if( name == "TDY" ) { frame = new Frame::v22::TDY(); }
        else if( name == "TEN" ) { frame = new Frame::v22::TEN(); }
        else if( name == "TFT" ) { frame = new Frame::v22::TFT(); }
        else if( name == "TIM" ) { frame = new Frame::v22::TIM(); }
        else if( name == "TKE" ) { frame = new Frame::v22::TKE(); }
        else if( name == "TLA" ) { frame = new Frame::v22::TLA(); }
        else if( name == "TLE" ) { frame = new Frame::v22::TLE(); }
        else if( name == "TMT" ) { frame = new Frame::v22::TMT(); }
        else if( name == "TOA" ) { frame = new Frame::v22::TOA(); }
        else if( name == "TOF" ) { frame = new Frame::v22::TOF(); }
        else if( name == "TOL" ) { frame = new Frame::v22::TOL(); }
        else if( name == "TOR" ) { frame = new Frame::v22::TOR(); }
        else if( name == "TOT" ) { frame = new Frame::v22::TOT(); }
        else if( name == "TP1" ) { frame = new Frame::v22::TP1(); }
        else if( name == "TP2" ) { frame = new Frame::v22::TP2(); }
        else if( name == "TP3" ) { frame = new Frame::v22::TP3(); }
        else if( name == "TP4" ) { frame = new Frame::v22::TP4(); }
        else if( name == "TPA" ) { frame = new Frame::v22::TPA(); }
        else if( name == "TPB" ) { frame = new Frame::v22::TPB(); }
        else if( name == "TRC" ) { frame = new Frame::v22::TRC(); }
        else if( name == "TRD" ) { frame = new Frame::v22::TRD(); }
        else if( name == "TRK" ) { frame = new Frame::v22::TRK(); }
        else if( name == "TSI" ) { frame = new Frame::v22::TSI(); }
        else if( name == "TSS" ) { frame = new Frame::v22::TSS(); }
        else if( name == "TT1" ) { frame = new Frame::v22::TT1(); }
        else if( name == "TT2" ) { frame = new Frame::v22::TT2(); }
        else if( name == "TT3" ) { frame = new Frame::v22::TT3(); }
        else if( name == "TXT" ) { frame = new Frame::v22::TXT(); }
        else if( name == "TXX" ) { frame = new Frame::v22::TXX(); }
        else if( name == "TYE" ) { frame = new Frame::v22::TYE(); }
        else if( name == "UFI" ) { frame = new Frame::v22::UFI(); }
        else if( name == "ULT" ) { frame = new Frame::v22::ULT(); }
        else if( name == "WAF" ) { frame = new Frame::v22::WAF(); }
        else if( name == "WAR" ) { frame = new Frame::v22::WAR(); }
        else if( name == "WAS" ) { frame = new Frame::v22::WAS(); }
        else if( name == "WCM" ) { frame = new Frame::v22::WCM(); }
        else if( name == "WCP" ) { frame = new Frame::v22::WCP(); }
        else if( name == "WPB" ) { frame = new Frame::v22::WPB(); }
        else if( name == "WXX" ) { frame = new Frame::v22::WXX(); }
        else
        {
            frame = new Frame::Unknown();
        }
        
        frame->impl->frame22    = header;
        frame->impl->frameSize  = size;
        frame->impl->data       = data;
        frame->impl->version    = version;
        
        frame->ProcessData();
        
        return frame;
    }
    
    AbstractFrame * AbstractFrame::IMPL::NewFrame( ID3v23Frame header, std::size_t size, uint8_t * data, Version version )
    {
        AbstractFrame   * frame;
        std::stringstream ss;
        std::string       name;
        
        ss << header.id[ 0 ];
        ss << header.id[ 1 ];
        ss << header.id[ 2 ];
        ss << header.id[ 3 ];
        
        name = ss.str();
        
             if( name == "AENC" ) { frame = new Frame::v23::AENC(); }
        else if( name == "APIC" ) { frame = new Frame::v23::APIC(); }
        else if( name == "COMM" ) { frame = new Frame::v23::COMM(); }
        else if( name == "COMR" ) { frame = new Frame::v23::COMR(); }
        else if( name == "ENCR" ) { frame = new Frame::v23::ENCR(); }
        else if( name == "EQUA" ) { frame = new Frame::v23::EQUA(); }
        else if( name == "ETCO" ) { frame = new Frame::v23::ETCO(); }
        else if( name == "GEOB" ) { frame = new Frame::v23::GEOB(); }
        else if( name == "GRID" ) { frame = new Frame::v23::GRID(); }
        else if( name == "IPLS" ) { frame = new Frame::v23::IPLS(); }
        else if( name == "LINK" ) { frame = new Frame::v23::LINK(); }
        else if( name == "MCDI" ) { frame = new Frame::v23::MCDI(); }
        else if( name == "MLLT" ) { frame = new Frame::v23::MLLT(); }
        else if( name == "OWNE" ) { frame = new Frame::v23::OWNE(); }
        else if( name == "PCNT" ) { frame = new Frame::v23::PCNT(); }
        else if( name == "POPM" ) { frame = new Frame::v23::POPM(); }
        else if( name == "POSS" ) { frame = new Frame::v23::POSS(); }
        else if( name == "PRIV" ) { frame = new Frame::v23::PRIV(); }
        else if( name == "RBUF" ) { frame = new Frame::v23::RBUF(); }
        else if( name == "RVAD" ) { frame = new Frame::v23::RVAD(); }
        else if( name == "RVRB" ) { frame = new Frame::v23::RVRB(); }
        else if( name == "SYLT" ) { frame = new Frame::v23::SYLT(); }
        else if( name == "SYTC" ) { frame = new Frame::v23::SYTC(); }
        else if( name == "TALB" ) { frame = new Frame::v23::TALB(); }
        else if( name == "TBPM" ) { frame = new Frame::v23::TBPM(); }
        else if( name == "TCOM" ) { frame = new Frame::v23::TCOM(); }
        else if( name == "TCON" ) { frame = new Frame::v23::TCON(); }
        else if( name == "TCOP" ) { frame = new Frame::v23::TCOP(); }
        else if( name == "TDAT" ) { frame = new Frame::v23::TDAT(); }
        else if( name == "TDLY" ) { frame = new Frame::v23::TDLY(); }
        else if( name == "TENC" ) { frame = new Frame::v23::TENC(); }
        else if( name == "TEXT" ) { frame = new Frame::v23::TEXT(); }
        else if( name == "TFLT" ) { frame = new Frame::v23::TFLT(); }
        else if( name == "TIME" ) { frame = new Frame::v23::TIME(); }
        else if( name == "TIT1" ) { frame = new Frame::v23::TIT1(); }
        else if( name == "TIT2" ) { frame = new Frame::v23::TIT2(); }
        else if( name == "TIT3" ) { frame = new Frame::v23::TIT3(); }
        else if( name == "TKEY" ) { frame = new Frame::v23::TKEY(); }
        else if( name == "TLAN" ) { frame = new Frame::v23::TLAN(); }
        else if( name == "TLEN" ) { frame = new Frame::v23::TLEN(); }
        else if( name == "TMED" ) { frame = new Frame::v23::TMED(); }
        else if( name == "TOAL" ) { frame = new Frame::v23::TOAL(); }
        else if( name == "TOFN" ) { frame = new Frame::v23::TOFN(); }
        else if( name == "TOLY" ) { frame = new Frame::v23::TOLY(); }
        else if( name == "TOPE" ) { frame = new Frame::v23::TOPE(); }
        else if( name == "TORY" ) { frame = new Frame::v23::TORY(); }
        else if( name == "TOWN" ) { frame = new Frame::v23::TOWN(); }
        else if( name == "TPE1" ) { frame = new Frame::v23::TPE1(); }
        else if( name == "TPE2" ) { frame = new Frame::v23::TPE2(); }
        else if( name == "TPE3" ) { frame = new Frame::v23::TPE3(); }
        else if( name == "TPE4" ) { frame = new Frame::v23::TPE4(); }
        else if( name == "TPOS" ) { frame = new Frame::v23::TPOS(); }
        else if( name == "TPUB" ) { frame = new Frame::v23::TPUB(); }
        else if( name == "TRCK" ) { frame = new Frame::v23::TRCK(); }
        else if( name == "TRDA" ) { frame = new Frame::v23::TRDA(); }
        else if( name == "TRSN" ) { frame = new Frame::v23::TRSN(); }
        else if( name == "TRSO" ) { frame = new Frame::v23::TRSO(); }
        else if( name == "TSIZ" ) { frame = new Frame::v23::TSIZ(); }
        else if( name == "TSRC" ) { frame = new Frame::v23::TSRC(); }
        else if( name == "TSSE" ) { frame = new Frame::v23::TSSE(); }
        else if( name == "TXXX" ) { frame = new Frame::v23::TXXX(); }
        else if( name == "TYER" ) { frame = new Frame::v23::TYER(); }
        else if( name == "UFID" ) { frame = new Frame::v23::UFID(); }
        else if( name == "USER" ) { frame = new Frame::v23::USER(); }
        else if( name == "USLT" ) { frame = new Frame::v23::USLT(); }
        else if( name == "WCOM" ) { frame = new Frame::v23::WCOM(); }
        else if( name == "WCOP" ) { frame = new Frame::v23::WCOP(); }
        else if( name == "WOAF" ) { frame = new Frame::v23::WOAF(); }
        else if( name == "WOAR" ) { frame = new Frame::v23::WOAR(); }
        else if( name == "WOAS" ) { frame = new Frame::v23::WOAS(); }
        else if( name == "WORS" ) { frame = new Frame::v23::WORS(); }
        else if( name == "WPAY" ) { frame = new Frame::v23::WPAY(); }
        else if( name == "WPUB" ) { frame = new Frame::v23::WPUB(); }
        else if( name == "WXXX" ) { frame = new Frame::v23::WXXX(); }
        else
        {
            frame = new Frame::Unknown();
        }
        
        frame->impl->frame23    = header;
        frame->impl->frameSize  = size;
        frame->impl->data       = data;
        frame->impl->version    = version;
        
        frame->ProcessData();
        
        return frame;
    }
    
    AbstractFrame::IMPL::IMPL( void ): version( 0, 0, 0 )
    {
        this->frameSize = 0;
        this->data      = NULL;
        
        memset( &( this->frame22 ), 0, sizeof( ID3v22Frame ) );
        memset( &( this->frame23 ), 0, sizeof( ID3v23Frame ) );
    }
    
    AbstractFrame::IMPL::~IMPL( void )
    {
        delete[] this->data;
    }
}
