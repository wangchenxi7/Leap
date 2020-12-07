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
asmlinkage int sys_get_leap_stats(long __user *tot_sc_pages,
				  long __user *sc_add, long __user *sc_del,
				  long __user *sc_find_succ, long __user *sc_find_tot,
				  long __user *free_swap, long __user *total_swap,
				  long __user *swap_rdahd_hit, long __user *trend_found,
				  long __user *swap_rdahd_entry) {

	long k_tot_sc_pages;
	long k_sc_add;
	long k_sc_del;
	long k_sc_find_succ;
	long k_sc_find_tot;
	long k_free_swap;
	long k_total_swap;
	long k_swap_rdahd_hit;
	long k_trend_found;
	long k_swap_rdahd_entry;
	// Leap stats. Declared in swap.h
	inner_get_leap_stats(&k_tot_sc_pages,
			     &k_sc_add, &k_sc_del,
			     &k_sc_find_succ, &k_sc_find_tot,
			     &k_free_swap, &k_total_swap,
			     &k_swap_rdahd_hit, &k_trend_found,
			     &k_swap_rdahd_entry);

	*tot_sc_pages = k_tot_sc_pages;
	*sc_add = k_sc_add;
	*sc_del = k_sc_del;
	*sc_find_succ = k_sc_find_succ;
	*sc_find_tot = k_sc_find_tot;
	*free_swap = k_free_swap;
	*total_swap = k_total_swap;
	*swap_rdahd_hit = k_swap_rdahd_hit;
	*trend_found = k_trend_found;
	*swap_rdahd_entry = k_swap_rdahd_entry;
	return 0;
}
EXPORT_SYMBOL(sys_get_swap_stats);