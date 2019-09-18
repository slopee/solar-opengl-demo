class Viewport
{
public:
	Viewport(int height, int width);

	void Setup();

	void SetActive(bool isActive);
	void SetPrimary(bool isPrimary);

private:
	int m_Height;
	int m_Width;
	bool m_IsActive;
	bool m_IsPrimary;
};