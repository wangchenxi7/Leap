/**
 * swap_stats.h - collect swap stats for profiling
 */

#ifndef _LINUX_SWAP_STATS_H
#define _LINUX_SWAP_STATS_H

#include <linux/swap.h>
// #include <linux/atomic.h>

extern atomic_t ondemand_swapin_number;
extern atomic_t prefetch_swapin_number;
extern atomic_t hit_on_swap_cache_number;

static inline void reset_swap_stats(void)
{
	atomic_set(&ondemand_swapin_number, 0);
	atomic_set(&prefetch_swapin_number, 0);
	atomic_set(&hit_on_swap_cache_number, 0);
}

static inline void ondemand_swapin_inc(void)
{
	atomic_inc(&ondemand_swapin_number);
}

static inline void prefetch_swapin_inc(void)
{
	atomic_inc(&prefetch_swapin_number);
}

static inline void prefetch_swapin_add(int val)
{
	atomic_add(val, &prefetch_swapin_number);
}

static inline void hit_on_swap_cache_inc(void)
{
	atomic_inc(&hit_on_swap_cache_number);
}

static inline int get_ondemand_swapin_number(void)
{
	return (int)atomic_read(&ondemand_swapin_number);
}

static inline int get_prefetch_swapin_number(void)
{
	return (int)atomic_read(&prefetch_swapin_number);
}

static inline int get_hit_on_swap_cache_number(void)
{
	return (int)atomic_read(&hit_on_swap_cache_number);
}

#endif /* _LINUX_SWAP_STATS_H */