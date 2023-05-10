class RingBuffer {
public:
	RingBuffer(unsigned int initSize);
	~RingBuffer();

	void write(const char* data);
	void read(char* outValua, unsigned int len);
	bool isEmpty();
	bool isFull();
	void clear();
	unsigned int size();
	void printAll();
private:
	unsigned int getUsedLen();
	void expandSize(int needExpandSize);
	void shrinkSize();

	unsigned int m_read = 0;
	unsigned int m_write = 0;
	unsigned int m_size = 0;
	char* m_data = nullptr;
};