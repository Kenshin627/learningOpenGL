#include <string>

class Texture
{
private:
	const char* m_filePath;
	unsigned int m_RendererID;
	int m_Width;
	int m_Height;
	int m_Bpp;
	unsigned char* m_localBuffer;
public:
	Texture(const std::string& filePath);
	~Texture();
	void bind(unsigned int slot) const;
	void unbind() const;
};