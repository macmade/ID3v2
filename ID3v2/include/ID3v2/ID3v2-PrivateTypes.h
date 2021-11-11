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
 * @header      ID3v2-PrivateTypes.h
 * @copyright   (c) 2014 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @abstract    ID3v2 private types
 */

#ifndef ID3V2_PRIVATE_TYPES
#define ID3V2_PRIVATE_TYPES

typedef struct
{
    char id[ 3 ];       /* ID3v2/file identifier   "ID3" */
    char version[ 2 ];  /* ID3v2 version           $03 00 */
    char flags;         /* ID3v2 flags             %abc00000 */
    char size[ 4 ];     /* ID3v2 size              4 * %0xxxxxxx */
}
ID3v2Header;

typedef struct
{
    char size[ 4 ];     /* Extended header size   $xx xx xx xx */
    char flags[ 2 ];    /* Extended Flags         $xx xx */
    char padding[ 4 ];  /* Size of padding        $xx xx xx xx */
}
ID3v2ExtendedHeader;

typedef struct
{
    char   id[ 3 ];     /* Frame ID       $xx xx xx xx (four characters) */
    char   size[ 3 ];   /* Size           $xx xx xx xx */
}
ID3v22Frame;

typedef struct
{
    char   id[ 4 ];     /* Frame ID       $xx xx xx xx (four characters) */
    char   size[ 4 ];   /* Size           $xx xx xx xx */
    char   flags[ 2 ];  /* Flags          $xx xx */
}
ID3v23Frame;

#endif /* ID3V2_PRIVATE_TYPES */
