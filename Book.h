#pragma once
//- Ư�� å�� �뿩 ���θ� �� �� �־�� �մϴ�.
//- å�� �̸����� �뿩 ���θ� �˻��ϰ� �뿩�� �ƴ� ��� �뿩�� �� �־�� �մϴ�.
//- å�� �۰��� �뿩 ���θ� �˻��ϰ� �뿩�� �ƴ� ��� �뿩�� �� �־�� �մϴ�.
//- å�� �ݳ��� �� �־�� �մϴ�.
//- ��� å�� ���� ���̵��� ���߱� ���� 3������ ���� �մϴ�.
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

