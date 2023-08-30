/*
 *	========================================================
 *
 *	MeBoot
 * 	Copyright Amlal El Mahrouss., all rights reserved.
 *
 * 	========================================================
 */

kBootBlockMagic: .asciiz "BootBlock"
kBootBlockGUID: .asciiz "C218439A-5939-4C9D-82AC-ADED46E9243C"
kBootBlockVersion: dw 1
kBootBlockNumBlocks: dw 1
kBootBlockSectorSz: dw 512
kBootBlockSectorStart: dw 528

;; OS

kSuperBlockName: .asciiz "MeOS_MeFS"
kSuperBlockMagic: dw 0xEDAD
kSuperBlockSectorEnd: dw 0
kSuperBlockSectorSz: dw 512
kSuperBlockSectorStart: dw 1024
kSuperBlockPartType: dw 1
kSuperBlockVer: dw 1
kSuperBlockFs: .asciiz "MeFS"

kSuperBlockReserved1: dq 0xFFFF
kSuperBlockReserved2: dq 0xFFFF
kSuperBlockReserved3: dq 0xFFFF

;; end of block

dw 0xAA55

