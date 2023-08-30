/*
 *	========================================================
 *
 *	MeKernel
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.align 4
.type name, @function
.text
.globl rt_do_context_switch

/* r3 = assigner stack, r4 = assignee stack */
rt_do_context_switch:

    lwz 0(%r4), 0(%r3)
    lwz 4(%r4), 4(%r3)
    lwz 8(%r4), 8(%r3)
    lwz 12(%r4), 12(%r3)
    lwz 16(%r4), 16(%r3)
    lwz 20(%r4), 20(%r4)
    lwz 24(%r4), 24(%r4)
    lwz 28(%r4), 28(%r4)
    lwz 32(%r4), 32(%r4)

    blr
