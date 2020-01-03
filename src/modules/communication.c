#include "communication.h"


struct cmi_opt *g_cmi_opt = NULL;

int8_t cmi_create(const fun_cmi_put put)
{
	g_cmi_opt = (struct cmi_opt *)malloc(sizeof(struct cmi_opt));
	if(!g_cmi_opt)
		return -1;

	g_cmi_opt->cmi_put = put;
	return 0;
}

void cmi_destory(void)
{
	if(g_cmi_opt)
		free(g_cmi_opt);
}



/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  实例化一帧数据，需要注意使用完成后需要释放内存
 *
 * @Param frm 需要实例化的帧
 *
 * @Returns   实例化后的内存指
 */
/* ----------------------------------------------------------------------------*/
static uint8_t *frm_instantiation(const struct cmi_frm *frm)
{
	uint8_t *obj = NULL;	

	if(!frm)
		return NULL; 

	obj = (uint8_t *)malloc(sizeof(struct cmi_frm) -\
		       	sizeof(uint8_t *) + frm->data_len );
	if(!obj)
		return NULL;

	memcpy(obj, CMI_FRM_HEAD, CMI_FRM_HEAD_LEN);
	memcpy(&obj[CMI_FRM_HEAD_LEN], frm, 7);	
	if(frm->data_len)
		memcpy(&obj[CMI_FRM_HEAD_LEN + 7], frm->data, frm->data_len);
	

	memcpy(&obj[CMI_FRM_HEAD_LEN + 7 + frm->data_len],\
		       CMI_FRM_TAIL, CMI_FRM_TAIL_LEN);


	return obj;
}

int8_t cmi_request(const uint16_t identification,
			const uint32_t data_len,
			const uint8_t *data)
{
	struct cmi_frm frm;
	uint8_t *obj = NULL;

	frm.type = CMI_REQUEST; 	
	frm.identification = identification;
	frm.data_len = data_len;
	frm.data = (uint8_t *)data;

	obj = frm_instantiation(&frm);
	

	g_cmi_opt->cmi_put(obj, sizeof(struct cmi_frm) -\
		       	sizeof(uint8_t *)+\
		    	data_len +\
			CMI_FRM_HEAD_LEN+\
		        CMI_FRM_TAIL_LEN);

	free(obj);
	return 0;
}

