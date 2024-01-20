using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
    public abstract class Strategy
    {
		public abstract void AlgorithmInterface();
    }
	public  class Strategy1: Strategy
	{
		public override void AlgorithmInterface()
		{
			
		}
	}
	public class Strategy2 : Strategy
	{
		public override void AlgorithmInterface()
		{

		}
	}
	public class Context
	{
		Strategy strategy;
		public Context(Strategy strategy)
		{
			this.strategy = strategy;
		}
		public void Deal()
		{
			strategy.AlgorithmInterface();
		}
	}
	public static class StrategyMain
	{
		public static void Init()
		{
			Context context = new Context(new Strategy2());
			context.Deal();
		}
		
	}
}
/*策略模式定义一系列算法，只写算法完成相同的工作，只是实现不同，Strategy层为Context定义了一系列可供重用的算法或行为；简化了单元测试，每个算法都有自己的类，可以通过自己的接口单独测试
 * 
 * 
 */
