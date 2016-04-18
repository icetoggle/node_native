#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <queue>
#include "sync.h"

using namespace native::sync;
using namespace std;
namespace native {
	namespace parallel {
		template <class T>
		class Channel
		{
		public:
			Channel(int _cap = 1) : cap(_cap){
				uv_cond_init(&up_cond);
				uv_cond_init(&down_cond);

			}
			~Channel() {
				uv_cond_destroy(&up_cond);
				uv_cond_destroy(&down_cond);
			}

			void push(T t) {
				Lock lock(&mutex);
				while (q.size() >= cap) {
					uv_cond_wait(up_cond, mutex.mutex);
				}
				q.push(t);
				uv_cond_signal(down_cond, mutex.mutex);
			}

			T& pop() {
				Lock lock(&mutex);
				while (q.empty()) {
					uv_cond_wait(down_cond, mutex.mutex);
				}
				T t = q.front();
				q.pop();
				if (q.size() < cap) {
					uv_cond_signal(up_cond, mutex.mutex);
				}
				return t;
			}

		private:
			queue<T> q;
			Mutex mutex;
			uv_cond_t up_cond;
			uv_cond_t down_cond;
			int cap;
		};
	}
}





#endif