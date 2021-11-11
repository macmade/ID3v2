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
 * @header      ID3v2-AbstractFrame.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 frame
 */

#ifndef ID3V2_ABSTRACT_FRAME
#define ID3V2_ABSTRACT_FRAME

namespace ID3v2
{
    class Tag;
    
    class AbstractFrame
    {
        friend class Tag;
        
        public:
            
            typedef enum
            {
                FlagTagAlterPreservation    = 0,
                FlagFileAlterPreservation   = 1,
                FlagReadOnly                = 2,
                FlagCompression             = 3,
                FlagEncryption              = 4,
                FlagGroupingIdentity        = 5
            }
            Flag;
            
            AbstractFrame( void );
            virtual ~AbstractFrame( void );
            
            std::string     GetName( void ) const;
            std::size_t     GetSize( void ) const;
            const uint8_t * GetData( void ) const;
            unsigned short  GetFlags( void ) const;
            bool            HasFlag( Flag flag ) const;
            
            virtual std::string GetDescription( void ) const = 0;
            
        protected:
            
            virtual void ProcessData( void ) = 0;
            
        private:
            
            static AbstractFrame * NewFrameFromFileHandle( FILE * fh, Version version );
            
            class  IMPL;
            IMPL * impl;
    };
}

#endif /* ID3V2_ABSTRACT_FRAME */
