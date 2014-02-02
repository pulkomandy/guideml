#pragma once

#include <stdio.h>
#include <pthread.h>

struct SignalSemaphore
{
	pthread_mutex_t sem;
};

static inline void InitSemaphore(struct SignalSemaphore* sem)
{
	sem->sem = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
}

static inline void ObtainSemaphore(struct SignalSemaphore* sem)
{
	pthread_mutex_lock(&sem->sem);
}

static inline void ReleaseSemaphore(struct SignalSemaphore* sem)
{
	pthread_mutex_unlock(&sem->sem);
}

// FIXME no way to delete a semaphore in Amiga API ? When do we call delete_sem
