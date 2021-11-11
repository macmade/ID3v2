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
 * @header      ID3v2-Frame-APIC.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 APIC frame
 */

#include <ID3v2.h>

namespace ID3v2
{
    namespace Frame
    {
        namespace v23
        {
            class APIC::IMPL
            {
                public:
                    
                    IMPL( void );
                    
                    uint8_t                textEncoding;
                    std::string            mimeType;
                    PictureType            pictureType;
                    std::string            pictureDescription;
                    std::vector< uint8_t > pictureData;
            };
                 
            APIC::APIC( void ): impl( new IMPL )
            {}
            
            APIC::~APIC( void )
            {
                delete this->impl;
            }
            
            void APIC::ProcessData( void )
            {
                const uint8_t * data;
                std::size_t     size;
                uint8_t         c;
                
                data = this->GetData();
                size = this->GetSize();
                
                if( data == NULL || size-- == 0 )
                {
                    return;
                }
                
                this->impl->textEncoding = *( data++ );
                
                while( size-- && ( c = *( data++ ) ) != 0 )
                {
                    this->impl->mimeType += static_cast< char >( c );
                }
                
                if( size-- == 0 )
                {
                    return;
                }
                
                c                       = *( data++ );
                this->impl->pictureType = ( c > 0x14 ) ? PictureType::Other : static_cast< PictureType >( c );
                
                while( size-- && ( c = *( data++ ) ) != 0 )
                {
                    this->impl->pictureDescription += static_cast< char >( c );
                }
                
                while( size-- )
                {
                    this->impl->pictureData.push_back( *( data++ ) );
                }
            }
            
            std::string APIC::GetDescription( void ) const
            {
                return "Attached picture";
            }
            
            uint8_t APIC::GetTextEncoding( void ) const
            {
                return this->impl->textEncoding;
            }
            
            std::string APIC::GetMimeType( void ) const
            {
                return this->impl->mimeType;
            }
            
            APIC::PictureType APIC::GetPictureType( void ) const
            {
                return this->impl->pictureType;
            }
            
            std::string APIC::GetPictureTypeString( void ) const
            {
                switch( this->impl->pictureType )
                {
                    case PictureType::FileIcon:              return "32x32 pixels file icon";
                    case PictureType::OtherFileIcon:         return "Other file icon";
                    case PictureType::CoverFront:            return "Cover (front)";
                    case PictureType::CoverBack:             return "Cover (back)";
                    case PictureType::LeafletPage:           return "Leaflet page";
                    case PictureType::Media:                 return "Media (e.g. lable side of CD)";
                    case PictureType::LeadArtist:            return "Lead artist/lead performer/soloist";
                    case PictureType::Artist:                return "Artist/performer";
                    case PictureType::Conductor:             return "Conductor";
                    case PictureType::Band:                  return "Band/Orchestra";
                    case PictureType::Composer:              return "Composer";
                    case PictureType::LyricistWriter:        return "Lyricist/text writer";
                    case PictureType::RecordingLocation:     return "Recording Location";
                    case PictureType::DuringRecording:       return "During recording";
                    case PictureType::DuringPerformance:     return "During performance";
                    case PictureType::MovieScreenCapture:    return "Movie/video screen capture";
                    case PictureType::BrightColouredFish:    return "A bright coloured fish";
                    case PictureType::Illustration:          return "Illustration";
                    case PictureType::BandLogotype:          return "Band/artist logotype";
                    case PictureType::PublisherLogotype:     return "Publisher/Studio logotype";
                    
                    default: break;
                }
                
                return "Other";
            }
            
            std::string APIC::GetPictureDescription( void ) const
            {
                return this->impl->pictureDescription;
            }
            
            std::vector< uint8_t > APIC::GetPictureData( void ) const
            {
                return this->impl->pictureData;
            }
            
            APIC::IMPL::IMPL( void ):
                textEncoding( 0 ),
                pictureType( PictureType::Other )
            {}
        }
    }
}
