#ifndef _ASM_X86_PVCLOCK_ABI_H
#define _ASM_X86_PVCLOCK_ABI_H
#ifndef __ASSEMBLY__

/*
 * These structs MUST NOT be changed.
 * They are the ABI between hypervisor and guest OS.
 * Both Xen and KVM are using this.
 *
 * pvclock_vcpu_time_info holds the system time and the tsc timestamp
 * of the last update. So the guest can use the tsc delta to get a
 * more precise system time.  There is one per virtual cpu.
 *
 * pvclock_wall_clock references the point in time when the system
 * time was zero (usually boot time), thus the guest calculates the
 * current wall clock by adding the system time.
 *
 * Protocol for the "version" fields is: hypervisor raises it (making
 * it uneven) before it starts updating the fields and raises it again
 * (making it even) when it is done.  Thus the guest can make sure the
 * time values it got are consistent by checking the version before
 * and after reading them.
 */

struct pvclock_vcpu_time_info {
	uint32_t   version;
	uint32_t   pad0;
	uint64_t   tsc_timestamp;
	uint64_t   system_time;
	uint32_t   tsc_to_system_mul;
	uint8_t    tsc_shift;
	uint8_t    flags;
	uint8_t    pad[2];
} __attribute__((__packed__)); /* 32 bytes */

struct pvclock_wall_clock {
	uint32_t   version;
	uint32_t   sec;
	uint32_t   nsec;
} __attribute__((__packed__));

#define PVCLOCK_TSC_STABLE_BIT	(1 << 0)
#define PVCLOCK_GUEST_STOPPED	(1 << 1)
/* PVCLOCK_COUNTS_FROM_ZERO broke ABI and can't be used anymore. */
#define PVCLOCK_COUNTS_FROM_ZERO (1 << 2)
#endif /* __ASSEMBLY__ */
#endif /* _ASM_X86_PVCLOCK_ABI_H */