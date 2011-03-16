#include <mysqlxx/Connection.h>
#include <mysqlxx/Query.h>


namespace mysqlxx
{

Query::Query(Connection * conn_, const std::string & query_string) : std::ostream(0), conn(conn_)
{
	init(&query_buf);

	if (!query_string.empty())
	{
		query_buf.str(query_string);
		seekp(0, std::ios::end);
	}

	imbue(std::locale::classic());
}

Query::Query(const Query & other) : std::ostream(0), conn(other.conn)
{
	init(&query_buf);
	imbue(std::locale::classic());

	*this << other.str();
}

Query & Query::operator= (const Query & other)
{
	conn = other.conn;

	seekp(0);
	clear();
	*this << other.str();
	
	return *this;
}

void Query::reset()
{
	seekp(0);
	clear();
	query_buf.str("");
}

void Query::executeImpl()
{
	std::string query_string = query_buf.str();
	if (mysql_real_query(conn->getDriver(), query_string.data(), query_string.size()))
		throw BadQuery(mysql_error(conn->getDriver()), mysql_errno(conn->getDriver()));
}

UseQueryResult Query::use()
{
	executeImpl();
	MYSQL_RES * res = mysql_use_result(conn->getDriver());
	if (!res)
		onError(conn->getDriver());

	return UseQueryResult(res, conn);
}

StoreQueryResult Query::store()
{
	executeImpl();
	MYSQL_RES * res = mysql_store_result(conn->getDriver());
	if (!res)
		checkError(conn->getDriver());

	return StoreQueryResult(res, conn);
}

void Query::execute()
{
	executeImpl();
}

UInt64 Query::insertID()
{
	return mysql_insert_id(conn->getDriver());
}

}
