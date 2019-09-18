#include "App/View/Viewport.h"
#include <glad/glad.h>

Viewport::Viewport(int height, int width) : 
	m_Height(height), 
	m_Width(width), 
	m_IsActive(true),
	m_IsPrimary(false)
{
}

void Viewport::Setup()
{
	if(!m_IsActive)
	{
		throw 20;
	}

	if(m_IsPrimary)
	{
		glViewport(0, 0, m_Width, m_Height);
	}
}

void Viewport::SetActive(bool isActive)
{
	
}

void Viewport::SetPrimary(bool isPrimary)
{
	
}