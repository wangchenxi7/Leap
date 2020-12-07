#include <linux/swap_stats.h>

// for on-demand swap-in counting
atomic_t ondemand_swapin_number;
atomic_t prefetch_swapin_number;
atomic_t hit_on_swap_cache_number;