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
 * @header      ID3v2-Frame-APIC.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 APIC frame
 */

#ifndef ID3V2_V23_FRAME_APIC
#define ID3V2_V23_FRAME_APIC

namespace ID3v2
{
    namespace Frame
    {
        namespace v23
        {
            class APIC: public AbstractFrame
            {
                public:
                        
                        enum class PictureType
                        {
                            Other               = 0x00,
                            FileIcon            = 0x01,
                            OtherFileIcon       = 0x02,
                            CoverFront          = 0x03,
                            CoverBack           = 0x04,
                            LeafletPage         = 0x05,
                            Media               = 0x06,
                            LeadArtist          = 0x07,
                            Artist              = 0x08,
                            Conductor           = 0x09,
                            Band                = 0x0A,
                            Composer            = 0x0B,
                            LyricistWriter      = 0x0C,
                            RecordingLocation   = 0x0D,
                            DuringRecording     = 0x0E,
                            DuringPerformance   = 0x0F,
                            MovieScreenCapture  = 0x10,
                            BrightColouredFish  = 0x11,
                            Illustration        = 0x12,
                            BandLogotype        = 0x13,
                            PublisherLogotype   = 0x14
                        };
                        
                        std::string to_string( PictureType value );
                        
                        APIC( void );
                        virtual ~APIC( void );
                        
                        std::string GetDescription( void ) const;
                        
                        uint8_t                GetTextEncoding( void )       const;
                        std::string            GetMimeType( void )           const;
                        PictureType            GetPictureType( void )        const;
                        std::string            GetPictureTypeString( void )  const;
                        std::string            GetPictureDescription( void ) const;
                        std::vector< uint8_t > GetPictureData( void )        const;
                        
                protected:
                        
                        void ProcessData( void );
                        
                private:
                        
                        class  IMPL;
                        IMPL * impl;
            };
        }
    }
}

#endif /* ID3V2_V23_FRAME_APIC */
