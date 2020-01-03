#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define CMI_FRM_HEAD_LEN (4)
#define CMI_FRM_TAIL_LEN (2)

#define CMI_FRM_HEAD ("\xfe\xf0\xf1\xf2")
#define CMI_FRM_TAIL ("\xfa\xfc")

enum CMI_TYPE{
	CMI_REQUEST,
	CMI_RESPONSE,
	CMI_REPORT,
};

struct cmi_frm{
	uint8_t type;
	uint16_t identification;
	uint32_t data_len;
	uint8_t *data;
}__attribute__((packed));


typedef int8_t (*fun_cmi_put)(const uint8_t *buf, \
				const uint32_t len);


struct cmi_opt{
	fun_cmi_put cmi_put;
};
int8_t cmi_create(const fun_cmi_put put);
int8_t cmi_request(const uint16_t identification,
			const uint32_t data_len,
			const uint8_t *data);

#endif
