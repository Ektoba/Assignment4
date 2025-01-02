#pragma once
//- 특정 책의 대여 여부를 알 수 있어야 합니다.
//- 책의 이름으로 대여 여부를 검색하고 대여가 아닌 경우 대여할 수 있어야 합니다.
//- 책의 작가로 대여 여부를 검색하고 대여가 아닌 경우 대여할 수 있어야 합니다.
//- 책을 반납할 수 있어야 합니다.
//- 모든 책의 재고는 난이도를 낮추기 위해 3권으로 통일 합니다.
class CBook
{
public:
	CBook(const std::string& title, const std::string& author);
	~CBook();
private:
	std::string m_title;
	std::string m_author;

public:
	std::string getTitle() const;
	std::string getAuthor() const;
};

