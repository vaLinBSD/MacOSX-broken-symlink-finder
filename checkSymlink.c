/*
 * Check if a symlink is corrupted.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char *
cleanValue( char *value, int length ) {

    static char rval[10000];

    char *src = value;
    char *dst = rval;

    for ( int i = 0; i < length; i += 1 ) {

	if ( i >= 10000 - 10 ) {

	    break;

	}

	if ( *src < ' ' || *src > '~' ) {

	    *dst++ = '.';

	} else {

	    *dst++ = *src;

	}

	src += 1;

    }

    *dst = '\0';

    return rval;

}

char *
toHex( char *value, int length ) {

    static char rval[20000];

    char *src, *dst;

    src = value;
    dst = rval;

    int offset = 0;
    for ( int i = 0; i < length; i += 1 ) {

	if ( dst - rval >= 20000 - 10 ) {

	    *dst++ = '.';
	    *dst++ = '.';
	    *dst++ = '.';

	    break;

	}

	if ( offset > 0 && ( offset & 3 ) == 0 ) {

	    *dst++ = ' ';

	}

	*dst++ = "0123456789abcdef"[ ( *src >> 4 ) & 0xf ];
	*dst++ = "0123456789abcdef"[ ( *src      ) & 0xf ];

	src += 1;

    }

    *dst = '\0';

    return rval;

}

int
main( int argc, char **argv ) {

    char linkValue[100000];

    if ( argc == 2 ) {

	char *linkName = argv[1];
	int linkLength = readlink( linkName, linkValue, sizeof(linkValue) );
	if ( linkLength < 0 ) {

	    perror( "checkSymlink(readlink)" );
	    exit( 1 );

	} else if ( linkLength == 0 ) {

	    printf( "checkSymlink:  symlink \"%s\" has zero length\n", linkName );

	} else {

	    linkValue[linkLength] = '\0';
	    int binaryOffset = -1;
	    for ( int i = 0; i < linkLength; i += 1 ) {

		if ( linkValue[i] < ' ' || linkValue[i] > '~' ) {

		    binaryOffset = i;
		    break;

		}

	    }

	    if ( binaryOffset >= 0 ) {

		printf( "checkSymlink:  symlink \"%s\" has binary data at offset %d:  \"%s\" == %s\n", linkName, binaryOffset, cleanValue( linkValue, linkLength ), toHex( linkValue, linkLength ) );

	    }

	}

    } else {

	printf( "Usage:  checkSymlink _link_\n" );
	exit( 1 );

    }

}
