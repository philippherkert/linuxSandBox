#pragma once

class MT
{
	public:
		MT();
		virtual ~MT();

	public:
		virtual void test1();
};


class MTD : public MT
{
	public:
		MTD();
		virtual ~MTD();

	public:
		virtual void test1();
};
