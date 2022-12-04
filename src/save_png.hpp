#ifndef OCOBWIPQFPFHWOCXYSRQMKIHKVBTJPNKGAHBYVGKCDYHIWWNHASRNQHEUNSVISJTNCIOGEBLK
#define OCOBWIPQFPFHWOCXYSRQMKIHKVBTJPNKGAHBYVGKCDYHIWWNHASRNQHEUNSVISJTNCIOGEBLK

// adapted from https://github.com/miloyip/svpng/blob/master/svpng.inc
inline void save_png( std::uint8_t* img,  unsigned w, unsigned h, int alpha, char const* const file_name ) noexcept
{
    constexpr unsigned t[] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c, 0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
    unsigned a = 1, b = 0, c, p = w * ( alpha ? 4 : 3 ) + 1, x, y, i;
    FILE* fp = fopen( file_name, "wb" );

    for ( i = 0; i < 8; i++ )
        fputc( ( "\x89PNG\r\n\32\n" )[i], fp );;

    {
        {
            fputc( ( 13 ) >> 24, fp );
            fputc( ( ( 13 ) >> 16 ) & 255, fp );
            fputc( ( ( 13 ) >> 8 ) & 255, fp );
            fputc( ( 13 ) & 255, fp );
        }
        c = ~0U;

        for ( i = 0; i < 4; i++ )
        {
            fputc( ( "IHDR" )[i], fp );
            c ^= ( ( "IHDR" )[i] );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
    }
    {
        {
            fputc( ( w ) >> 24, fp );
            c ^= ( ( w ) >> 24 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            fputc( ( ( w ) >> 16 ) & 255, fp );
            c ^= ( ( ( w ) >> 16 ) & 255 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            fputc( ( ( w ) >> 8 ) & 255, fp );
            c ^= ( ( ( w ) >> 8 ) & 255 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            fputc( ( w ) & 255, fp );
            c ^= ( ( w ) & 255 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
    }
    {
        {
            fputc( ( h ) >> 24, fp );
            c ^= ( ( h ) >> 24 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            fputc( ( ( h ) >> 16 ) & 255, fp );
            c ^= ( ( ( h ) >> 16 ) & 255 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            fputc( ( ( h ) >> 8 ) & 255, fp );
            c ^= ( ( ( h ) >> 8 ) & 255 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            fputc( ( h ) & 255, fp );
            c ^= ( ( h ) & 255 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
    }
    {
        fputc( 8, fp );
        c ^= ( 8 );
        c = ( c >> 4 ) ^ t[c & 15];
        c = ( c >> 4 ) ^ t[c & 15];
    }
    {
        fputc( alpha ? 6 : 2, fp );
        c ^= ( alpha ? 6 : 2 );
        c = ( c >> 4 ) ^ t[c & 15];
        c = ( c >> 4 ) ^ t[c & 15];
    }

    for ( i = 0; i < 3; i++ )
    {
        fputc( ( "\0\0\0" )[i], fp );
        c ^= ( ( "\0\0\0" )[i] );
        c = ( c >> 4 ) ^ t[c & 15];
        c = ( c >> 4 ) ^ t[c & 15];
    }

    {
        fputc( ( ~c ) >> 24, fp );
        fputc( ( ( ~c ) >> 16 ) & 255, fp );
        fputc( ( ( ~c ) >> 8 ) & 255, fp );
        fputc( ( ~c ) & 255, fp );
    }

    {
        {
            fputc( ( 2 + h * ( 5 + p ) + 4 ) >> 24, fp );
            fputc( ( ( 2 + h * ( 5 + p ) + 4 ) >> 16 ) & 255, fp );
            fputc( ( ( 2 + h * ( 5 + p ) + 4 ) >> 8 ) & 255, fp );
            fputc( ( 2 + h * ( 5 + p ) + 4 ) & 255, fp );
        }
        c = ~0U;

        for ( i = 0; i < 4; i++ )
        {
            fputc( ( "IDAT" )[i], fp );
            c ^= ( ( "IDAT" )[i] );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
    }

    for ( i = 0; i < 2; i++ )
    {
        fputc( ( "\x78\1" )[i], fp );
        c ^= ( ( "\x78\1" )[i] );
        c = ( c >> 4 ) ^ t[c & 15];
        c = ( c >> 4 ) ^ t[c & 15];
    }

    for ( y = 0; y < h; y++ )
    {
        {
            fputc( y == h - 1, fp );
            c ^= ( y == h - 1 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            {
                fputc( ( p ) & 255, fp );
                c ^= ( ( p ) & 255 );
                c = ( c >> 4 ) ^ t[c & 15];
                c = ( c >> 4 ) ^ t[c & 15];
            }
            {
                fputc( ( ( p ) >> 8 ) & 255, fp );
                c ^= ( ( ( p ) >> 8 ) & 255 );
                c = ( c >> 4 ) ^ t[c & 15];
                c = ( c >> 4 ) ^ t[c & 15];
            }
        }
        {
            {
                fputc( ( ~p ) & 255, fp );
                c ^= ( ( ~p ) & 255 );
                c = ( c >> 4 ) ^ t[c & 15];
                c = ( c >> 4 ) ^ t[c & 15];
            }
            {
                fputc( ( ( ~p ) >> 8 ) & 255, fp );
                c ^= ( ( ( ~p ) >> 8 ) & 255 );
                c = ( c >> 4 ) ^ t[c & 15];
                c = ( c >> 4 ) ^ t[c & 15];
            }
        }
        {
            {
                fputc( 0, fp );
                c ^= ( 0 );
                c = ( c >> 4 ) ^ t[c & 15];
                c = ( c >> 4 ) ^ t[c & 15];
            }
            a = ( a + ( 0 ) ) % 65521;
            b = ( b + a ) % 65521;
        }

        for ( x = 0; x < p - 1; x++, img++ )
        {
            {
                fputc( *img, fp );
                c ^= ( *img );
                c = ( c >> 4 ) ^ t[c & 15];
                c = ( c >> 4 ) ^ t[c & 15];
            }
            a = ( a + ( *img ) ) % 65521;
            b = ( b + a ) % 65521;
        }
    }

    {
        {
            fputc( ( ( b << 16 ) | a ) >> 24, fp );
            c ^= ( ( ( b << 16 ) | a ) >> 24 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            fputc( ( ( ( b << 16 ) | a ) >> 16 ) & 255, fp );
            c ^= ( ( ( ( b << 16 ) | a ) >> 16 ) & 255 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            fputc( ( ( ( b << 16 ) | a ) >> 8 ) & 255, fp );
            c ^= ( ( ( ( b << 16 ) | a ) >> 8 ) & 255 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
        {
            fputc( ( ( b << 16 ) | a ) & 255, fp );
            c ^= ( ( ( b << 16 ) | a ) & 255 );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
    }

    {
        fputc( ( ~c ) >> 24, fp );
        fputc( ( ( ~c ) >> 16 ) & 255, fp );
        fputc( ( ( ~c ) >> 8 ) & 255, fp );
        fputc( ( ~c ) & 255, fp );
    }

    {
        {
            fputc( ( 0 ) >> 24, fp );
            fputc( ( ( 0 ) >> 16 ) & 255, fp );
            fputc( ( ( 0 ) >> 8 ) & 255, fp );
            fputc( ( 0 ) & 255, fp );
        }
        c = ~0U;

        for ( i = 0; i < 4; i++ )
        {
            fputc( ( "IEND" )[i], fp );
            c ^= ( ( "IEND" )[i] );
            c = ( c >> 4 ) ^ t[c & 15];
            c = ( c >> 4 ) ^ t[c & 15];
        }
    }

    {
        fputc( ( ~c ) >> 24, fp );
        fputc( ( ( ~c ) >> 16 ) & 255, fp );
        fputc( ( ( ~c ) >> 8 ) & 255, fp );
        fputc( ( ~c ) & 255, fp );
    }

    fclose( fp );
}

#endif//OCOBWIPQFPFHWOCXYSRQMKIHKVBTJPNKGAHBYVGKCDYHIWWNHASRNQHEUNSVISJTNCIOGEBLK

