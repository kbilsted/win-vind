#ifndef _DEBUG_HPP
#define _DEBUG_HPP

namespace vind
{
    namespace util {
#ifdef DEBUG
        void bench_start() ;
        int bench_stop() ;
#endif
    }
}
#endif