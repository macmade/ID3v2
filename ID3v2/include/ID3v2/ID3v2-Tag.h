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
 * @header      ID3v2-Tag.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 tag
 */

#ifndef ID3V2_TAG
#define ID3V2_TAG

namespace ID3v2
{
    class Tag
    {
        public:
            
            typedef enum
            {
                FlagUnsynchronisation       = 0,
                FlagExtendedHeader          = 1,
                FlagExperimentalIndicator   = 2
            }
            Flag;
            
            Tag( std::string path );
            Tag( const Tag & tag );
            
            virtual ~Tag( void );
            
            Tag & operator =( const Tag & tag );
            
            bool                            IsValid( void ) const;
            Version                         GetVersion( void ) const;
            unsigned char                   GetFlags( void ) const;
            bool                            HasFlag( Flag flag ) const;
            std::size_t                     GetSize( void );
            ExtendedHeader                * GetExtendedHeader( void );
            std::vector< AbstractFrame * >  GetFrames( void ) const;
            AbstractFrame                 * GetFrameWithName( std::string name ) const;
            
        private:
            
            class  IMPL;
            IMPL * impl;
    };
}

#endif /* ID3V2_TAG */
