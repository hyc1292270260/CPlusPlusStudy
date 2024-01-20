using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
    abstract class Unitednations
    {
		//声明发送消息
		public abstract void Declare(string message, Country colleague);
    }
	abstract class Country
	{
		protected Unitednations mediator;
		public Country(Unitednations mediator)
		{
			this.mediator = mediator;
		}

	}
	class UnitednationsAnlihui : Unitednations
	{
		//具体中介者，认识所有对象
		private Country1 country1;
		private Country2 country2;
		public override void Declare(string message, Country colleague)
		{
			//发送消息
			if (colleague == country1)
			{
				country2.Getmessage(message);
			}
			else if (colleague == country2)
			{
				country1.Getmessage(message);
			}
		}
		public void SetCountry1(Country1 country1)
		{
			this.country1 = country1;
		}
		public void SetCountry2(Country2 country2)
		{
			this.country2 = country2;
		}
	}
	class Country1 : Country
	{
		public Country1(Unitednations mediator) : base(mediator)
		{

		}
		public void Declare(string message)
		{
			mediator.Declare(message, this);
		}
		public void Getmessage(string message)
		{
			//得到消息
		}
	}
	class Country2 : Country
	{
		public Country2(Unitednations mediator) : base(mediator)
		{

		}
		public void Declare(string message)
		{
			mediator.Declare(message, this);
		}
		public void Getmessage(string message)
		{
			//得到消息
		}
	}
	public static class MediatorMain
	{
		public static void Init()
		{
			UnitednationsAnlihui anlihui = new UnitednationsAnlihui();

			Country1 country1 = new Country1(anlihui);
			Country2 country2 = new Country2(anlihui);

			anlihui.SetCountry1(country1);
			anlihui.SetCountry2(country2);

			country1.Declare("1");
			country2.Declare("2");

		}

	}
}
/*中介者模式：把对象之间的协调放在了中介者身上，减少了对象之间耦合，但是中介者要认识所有对象，一般用于一组对象以定义良好但是复杂通讯的场合，窗口或Web页面各组件之间的交互
 */
