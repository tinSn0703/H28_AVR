
/*
includeするだけのヘッダファイルそれ以上でもそれ以下でもない
 H28 05 18 ver0.0.0
*/

#pragma once

#ifndef _H28_AVR_H_
#	error "Include <H28_AVR.h>"
#endif

#include "H28_U_C_UART_base.h"
#include "H28_U_C_UART_R.h"

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)
#	include "H28_U_C_UART_R2.h"
#endif

#include "H28_U_C_UART_T.h"
#include "H28_U_C_UART.h"