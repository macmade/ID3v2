/*******************************************************************************
 * Copyright (c) 2014, Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      ID3v2-AbstractFrame.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 frame
 */

#ifndef __ID3V2_ABSTRACT_FRAME__
#define __ID3V2_ABSTRACT_FRAME__

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
            const char *    GetData( void ) const;
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

#endif /* __ID3V2_ABSTRACT_FRAME__ */
