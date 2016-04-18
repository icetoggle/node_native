#ifndef __SYNC_H__
#define __SYNC_H__

#include <uv.h>

namespace native {
	namespace sync {
		class Mutex {
		public:
			Mutex() {
				uv_mutex_init(&mutex);
			}

			Mutex() {
				uv_mutex_destroy(&mutex);
			}

			void lock() {
				uv_mutex_lock(&mutex);
			}

			void unlock() {
				uv_mutex_unlock(&mutex);
			}
			uv_mutex_t mutex;
		};

		class Lock
		{
		public:
			Lock(Mutex *_mutex) :mutex(_mutex) {
				mutex->lock();
			}
			~Lock() {
				mutex->unlock();
			}

		private:
			Mutex* mutex;
		};
	}

}


#endif