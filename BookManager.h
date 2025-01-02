#pragma once
class CBook;

class CBookManager :
	public CSingleton<CBookManager>
{
public:
	CBookManager();
	~CBookManager();
private:
	std::unique_ptr<class CBookContainer> m_Container;
	std::unique_ptr<class CBorrowManager> m_Borrow;
public:
	bool Init();
	void InitStock();
	void borrowBook(const std::string& title);
	void returnBook(const std::string& title);
	void addBook(const std::string& title, const std::string& author);
	std::vector<CBook*> findBookByTitle(const std::string& title);
	std::vector<CBook*> findBookByAuthor(const std::string& author);
	std::vector<CBook*> getAllBooks();
	std::unordered_map<CBook*, int>& getAllStock();
};