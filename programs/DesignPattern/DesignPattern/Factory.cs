using System;

namespace DesignPattern
{
	class Factory
	{
		static void Main(string[] args)
		{
			Operation operation = OperationFactory.CreateOperate("+");
			operation.Num1 = 1;
			operation.Num2 = 1;
			double ret = operation.GetResult();


			IOperationFactory addfactory = new AddFactory();
			Operation operation1 = addfactory.CreateFactory();
		}
		public class Operation
		{
			private double _num2;
			public double Num1 { get; set; }
			public double Num2
			{
				get { return _num2; }
				set { _num2 = value; }
			}
			public virtual double GetResult()
			{
				double result = 0;
				return result;
			}
		}
		public class Add : Operation
		{
			public override double GetResult()
			{
				return Num1 + Num2;
			}
		}
		public class Sub : Operation
		{
			public override double GetResult()
			{
				return Num1 - Num2;
			}
		}
		public class Mul : Operation
		{
			public override double GetResult()
			{
				return Num1 * Num2;
			}
		}
		public class Div : Operation
		{
			public override double GetResult()
			{
				if (Num2 == 0)
				{
					throw new Exception("除数为0");
				}
				return Num1 / Num2;
			}
		}
		public class OperationFactory
		{
			public static Operation CreateOperate(String operate)
			{

				switch (operate)
				{
					case "+":
						return new Add();
					case "-":
						return new Sub();
					case "*":
						return new Mul();
					case "/":
						return new Div();
				}
				return null;
			}
		}
		public interface IOperationFactory
		{
			Operation CreateFactory();
		}
		public class AddFactory : IOperationFactory
		{
			public Operation CreateFactory()
			{
				return new Add();
			}
		}
	}
}
/*简单工厂违背开闭原则，工厂方法每增加一个产品就要增加一个产品工厂类（替换switch case）
 * 可以设置为静态工厂
 * 抽象工厂 一个工厂可以生产不止一个产品类，
 */