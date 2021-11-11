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
 * @file        main.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 test executable
 */

#include <ID3v2.h>

int main( void )
{
    ID3v2::Tag                                      tag( "/Users/macmade/Desktop/song.mp3" );
    ID3v2::AbstractFrame                          * frame;     
    std::vector< ID3v2::AbstractFrame * >           frames;
    std::vector< ID3v2::AbstractFrame * >::iterator it;
    
    if( tag.IsValid() == false )
    {
        std::cout << "Invalid ID3v2 file" << std::endl;
        
        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "ID3v2 version:          " << tag.GetVersion().GetStringValue() << std::endl;
        
        std::cout << "Unsynchronisation:      " << ( ( tag.HasFlag( ID3v2::Tag::FlagUnsynchronisation     ) ) ? "Yes" : "No" ) << std::endl;
        std::cout << "Extended header:        " << ( ( tag.HasFlag( ID3v2::Tag::FlagExtendedHeader        ) ) ? "Yes" : "No" ) << std::endl;
        std::cout << "Experimental indicator: " << ( ( tag.HasFlag( ID3v2::Tag::FlagExperimentalIndicator ) ) ? "Yes" : "No" ) << std::endl;
        
        std::cout << "Header size:            " << tag.GetSize() << std::endl;
        
        frames = tag.GetFrames();
        
        for( it = frames.begin(); it != frames.end(); ++it )
        {
            frame = *( it );
            
            std::cout << std::endl;
            std::cout << "Frame: " << frame->GetName() << " (" << frame->GetDescription() << ")" << std::endl;
            std::cout << std::endl;
            std::cout << "    - Size:                    " << frame->GetSize() << std::endl;
            std::cout << "    - Tag alter preservation:  " << ( ( frame->HasFlag( ID3v2::AbstractFrame::FlagTagAlterPreservation  ) ) ? "No"  : "Yes" ) << std::endl;
            std::cout << "    - File alter preservation: " << ( ( frame->HasFlag( ID3v2::AbstractFrame::FlagFileAlterPreservation ) ) ? "No"  : "Yes" ) << std::endl;
            std::cout << "    - Read only:               " << ( ( frame->HasFlag( ID3v2::AbstractFrame::FlagReadOnly              ) ) ? "Yes" : "No" ) << std::endl;
            std::cout << "    - Compression:             " << ( ( frame->HasFlag( ID3v2::AbstractFrame::FlagCompression           ) ) ? "Yes" : "No" ) << std::endl;
            std::cout << "    - Encryption:              " << ( ( frame->HasFlag( ID3v2::AbstractFrame::FlagCompression           ) ) ? "Yes" : "No" ) << std::endl;
            std::cout << "    - Grouping identity:       " << ( ( frame->HasFlag( ID3v2::AbstractFrame::FlagGroupingIdentity      ) ) ? "Yes" : "No" ) << std::endl;
        }
        
        {
            ID3v2::Frame::v23::APIC * apic;
            
            apic = dynamic_cast< ID3v2::Frame::v23::APIC * >( tag.GetFrameWithName( "APIC" ) );
            
            if( apic != nullptr )
            {
                using std::to_string;
                
                std::cout << std::endl;
                std::cout << "APIC:" << std::endl;
                std::cout << "    - Text encoding:       " << static_cast< unsigned int >( apic->GetTextEncoding() ) << std::endl;
                std::cout << "    - MIME type:           " << apic->GetMimeType() << std::endl;
                std::cout << "    - Picture type:        " << apic->GetPictureTypeString() << std::endl;
                std::cout << "    - Picture description: " << apic->GetPictureDescription() << std::endl;
                std::cout << "    - Picture data size:   " << apic->GetPictureData().size() << std::endl;
            }
        }
    }
    
    return EXIT_SUCCESS;
}
