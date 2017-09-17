//
//      Code taken from https://gist.github.com/mortennobel/4648058.
//          All creds go to this geezer ^^^^^^
//


#ifndef GLERROR_H
#define GLERROR_H

void _check_gl_error(const char *file, int line);

///
/// Usage
/// [... some opengl calls]
/// check_gl_error();
///
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

#endif // GLERROR_H