
#ifndef PHP_IMAGEMAGICK_VERSION_DEFS_H
# define PHP_IMAGEMAGICK_VERSION_DEFS_H

// Q) Why are the defines done in this file?
//
// A) Checking whether an ImageMagick function is available _and_ usable is
// annoyingly difficult. It's pretty common for new functions to be introduced
// in patch releases, (e.g. 6.5.4-8) rather than in minor releases (6.5.5-0).
//
// Additionally, the api for new functions often changes quite rapidly in the
// first few versions it is available in, which means we can't just check for
// the presence of the symbol
//
// Because of those two things, the sanest thing to do is to support features
// based on the minimum minor version from which they are continually
// available and stable.
//
// Any mistake in which version is required for a feature can be fixed in a
// single place, rather than having to have duplicated info elsewhere.


#if MagickLibVersion >= 0x700
  #if MagickLibVersion >= 0x702
    #define IM_HAVE_IMAGICK_SETIMAGEINTERPOLATEMETHOD 1
  #endif
#elif MagickLibVersion >= 0x631
    #define IM_HAVE_IMAGICK_SETIMAGEINTERPOLATEMETHOD 1
#endif


// The above is sub-optimal as it's hard to read. It'd be better to do
// something like the below:

//#define MAGICK_LIB_RANGE(NAME, IM6_VERSION, IM7_VERSION) \
//#if MagickLibVersion >= 0x700 \
//  #if MagickLibVersion >= IM7_VERSION \
//      #define IM_HAVE_##NAME 1 \
//  #endif \
//#elif MagickLibVersion >= 0x600 \
//  #if MagickLibVersion >= IM6_VERSION \
//    #define IM_HAVE_##NAME 1 \
//  #endif \
//#endif

// MAGICK_LIB_RANGE(IMAGICK_SETIMAGEINTERPOLATEMETHOD, 0x631, 0x702)

// But this type of macro expansion is not possible.
//
// https://stackoverflow.com/questions/48431325/is-it-possible-to-define-macro-inside-macro
// "The resulting completely macro-replaced preprocessing token sequence is not
// processed as a preprocessing directive even if it resembles one,..."
//
// An alternative would be to use code generation to build the define file as
// part of the build process. However that would involve looking at m4 config files.

#endif /* PHP_IMAGEMAGICK_VERSION_DEFS_H */