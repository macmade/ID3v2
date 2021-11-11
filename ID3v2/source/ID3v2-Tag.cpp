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
 * @header      ID3v2-Tag.cpp
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 tag
 */

#include <ID3v2.h>
#include <ID3v2/ID3v2-PrivateTypes.h>

namespace ID3v2
{
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpadded"
    #endif
    
    class Tag::IMPL
    {
        public:
            
            IMPL( void );
            ~IMPL( void );
            
            void ParseFile( std::string path );
            
            bool                           valid;
            Version                        version;
            ID3v2Header                    header;
            std::size_t                    headerSize;
            ExtendedHeader               * extendedHeader;
            std::vector< AbstractFrame * > frames;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
    
    Tag::Tag( std::string path ): impl( new IMPL )
    {
        this->impl->ParseFile( path );
    }
    
    Tag::Tag( const Tag & tag ): impl( new IMPL )
    {
        this->impl->valid = tag.impl->valid;
    }
    
    Tag::~Tag( void )
    {
        delete this->impl;
    }
    
    Tag & Tag::operator =( const Tag & tag )
    {
        this->impl->valid = tag.impl->valid;
        
        return *( this );
    }
    
    bool Tag::IsValid( void ) const
    {
        return this->impl->valid;
    }
    
    Version Tag::GetVersion( void ) const
    {
        if( this->IsValid() == false )
        {
            return Version( 0, 0, 0 );
        }
        
        return this->impl->version;
    }
    
    unsigned char Tag::GetFlags( void ) const
    {
        if( this->IsValid() == false )
        {
            return 0;
        }
        
        return static_cast< unsigned char >( this->impl->header.flags );
    }
    
    bool Tag::HasFlag( Flag flag ) const
    {
        if( this->IsValid() == false )
        {
            return false;
        }
        
        switch( flag )
        {
            case FlagUnsynchronisation:     return ( this->impl->header.flags & 0x80 ) ? true : false;
            case FlagExtendedHeader:        return ( this->impl->header.flags & 0x40 ) ? true : false;
            case FlagExperimentalIndicator: return ( this->impl->header.flags & 0x20 ) ? true : false;
        }
        
        return false;
    }
    
    std::size_t Tag::GetSize( void )
    {
        if( this->IsValid() == false )
        {
            return 0;
        }
        
        return this->impl->headerSize;
    }
    
    ExtendedHeader * Tag::GetExtendedHeader( void )
    {
        if( this->IsValid() == false )
        {
            return NULL;
        }
        
        return this->impl->extendedHeader;
    }
    
    std::vector< AbstractFrame * > Tag::GetFrames( void ) const
    {
        if( this->IsValid() == false )
        {
            return std::vector< AbstractFrame * >();
        }
        
        return this->impl->frames;
    }
    
    AbstractFrame * Tag::GetFrameWithName( std::string name ) const
    {
        std::vector< AbstractFrame * >::iterator it;
        AbstractFrame                          * frame;
        
        if( this->IsValid() == false )
        {
            return NULL;
        }
        
        for( it = this->impl->frames.begin(); it != this->impl->frames.end(); ++it )
        {
            frame = *( it );
            
            if( frame != NULL && frame->GetName() == name )
            {
                return frame;
            }
        }
        
        return NULL;
    }
    
    Tag::IMPL::IMPL( void ): version( 0, 0, 0 )
    {
        this->valid             = false;
        this->headerSize        = 0;
        this->extendedHeader    = NULL;
        
        memset( &( this->header ), 0, sizeof( ID3v2Header ) );
    }
    
    Tag::IMPL::~IMPL( void )
    {
        std::vector< AbstractFrame * >::iterator it;
        
        delete this->extendedHeader;
        
        for( it = this->frames.begin(); it != this->frames.end(); ++it )
        {
            delete *( it );
        }
    }
    
    void Tag::IMPL::ParseFile( std::string path )
    {
        FILE * fh;
        
        this->valid = false;
        
        #ifdef _WIN32
        fopen_s( &fh, path.c_str(), "rb" );
        #else
        fh = fopen( path.c_str(), "rb" );
        #endif
        
        if( fh == NULL )
        {
            return;
        }
        
        if( fread( &( this->header ), 1, sizeof( ID3v2Header ), fh ) != sizeof( ID3v2Header ) )
        {
            goto end;
        }
        
        if( this->header.id[ 0 ] != 'I' || this->header.id[ 1 ] != 'D' || this->header.id[ 2 ] != '3' )
        {
            goto end;
        }
        
        this->version = Version
        (
            2,
            static_cast< unsigned int >( this->header.version[ 0 ] ),
            static_cast< unsigned int >( this->header.version[ 1 ] )
        );
        
        {
            std::size_t s1;
            std::size_t s2;
            std::size_t s3;
            std::size_t s4;
            
            s1   = static_cast< std::size_t >( this->header.size[ 0 ] );
            s2   = static_cast< std::size_t >( this->header.size[ 1 ] );
            s3   = static_cast< std::size_t >( this->header.size[ 2 ] );
            s4   = static_cast< std::size_t >( this->header.size[ 3 ] );
            s1  &= 0x7F;
            s2  &= 0x7F;
            s3  &= 0x7F;
            s4  &= 0x7F;
            s1 <<= 21;
            s2 <<= 14;
            s3 <<= 7;
            
            this->headerSize = s1 | s2 | s3 | s4;
        }
        
        if( this->header.flags & 0x40 )
        {
            {
                ExtendedHeader * exHeader;
                
                exHeader = ExtendedHeader::NewExtendedHeaderFromFileHandle( fh );
                
                if( exHeader == NULL )
                {
                    goto end;
                }
                
                this->extendedHeader = exHeader;
            }
        }
        
        while( static_cast< std::size_t >( ftell( fh ) ) < this->headerSize )
        {
            {
                AbstractFrame * frame;
                
                frame = AbstractFrame::NewFrameFromFileHandle( fh, this->version );
                
                if( frame == NULL )
                {
                    goto end;
                }
                
                if( frame->GetSize() == 0 && dynamic_cast< Frame::Unknown * >( frame ) == nullptr )
                {
                    delete frame;
                    
                    break;
                }
                
                this->frames.push_back( frame );
            }
        }
        
        this->valid = true;
            
        end:
        
        fclose( fh );
    }
}
