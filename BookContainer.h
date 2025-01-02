#pragma once

class CBookContainer
{
	friend class CBookManager;
	typedef std::vector<std::unique_ptr<class CBook>>::iterator iter;
	typedef std::unique_ptr<class CBook> PBOOK;
public:
	CBookContainer();
	~CBookContainer();
private:
	std::vector<PBOOK> m_vecBook;
public:
	void addBook(const std::string& title, const std::string& author);
	std::vector<class CBook*> findBookByTitle(const std::string& title);
	std::vector<class CBook*> findBookByAuthor(const std::string& author);
	std::vector<class CBook*> getAllBooks();
public:
	void sort();
};

