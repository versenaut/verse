
typedef struct{
	void	*oldest;
	void	*newest;
	uint32	packet_id;
	uint32	seconds;
}VNetInQueue;

typedef struct{
	void	*newer;
	void	*older;
	char	data[1500];
	size_t	size;
}VNetInPacked;

extern void v_niq_clear(VNetInQueue *queue);
extern VNetInPacked *v_niq_get(VNetInQueue *queue, size_t *length);
extern void v_niq_release(VNetInQueue *queue, VNetInPacked *p);
extern char *v_niq_store(VNetInQueue *queue, size_t length, unsigned int packet_id);

extern boolean v_niq_time_out(const VNetInQueue *queue);