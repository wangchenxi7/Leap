#include <linux/swap_stats.h>
#include "extended_syscalls.h"

asmlinkage int sys_reset_swap_stats(void) {
	reset_swap_stats();
	// reset Leap stats. Declared in swap.h
	init_stat();
	return 0;
}
EXPORT_SYMBOL(sys_reset_swap_stats);

asmlinkage int sys_get_swap_stats(int __user *on_demand_swapin_num,
				  int __user *prefetch_swapin_num,
				  int __user *hiton_swap_cache_num) {
	*on_demand_swapin_num = get_ondemand_swapin_number();
	*prefetch_swapin_num  = get_prefetch_swapin_number();
	*hiton_swap_cache_num = get_hit_on_swap_cache_number();

	return 0;
}

// sc for "swap cache"
asmlinkage int sys_get_leap_stats(long __user *stats_buf) {
	// Leap stats. Declared in swap.h
	inner_get_leap_stats(stats_buf);

	return 0;
}
EXPORT_SYMBOL(sys_get_swap_stats);