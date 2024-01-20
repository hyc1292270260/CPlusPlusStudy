using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
    abstract class Visitor
    {
		public abstract void VisitElementA(ConcreteElementA elementA);
		public abstract void VisitElementB(ConcreteElementB elementB);
	}
	abstract class Element
	{
		//数据接口
		public abstract void Accept(Visitor visitor);
	}
	class ConcreteElementA:Element
	{
		public override void Accept(Visitor visitor)
		{
			visitor.VisitElementA(this);
		}
	}
	class ConcreteElementB : Element
	{
		public override void Accept(Visitor visitor)
		{
			visitor.VisitElementB(this);
		}
	}
	class ConcreteVisitor1 : Visitor
	{
		public override void VisitElementA(ConcreteElementA elementA)
		{
			
		}
		public override void VisitElementB(ConcreteElementB elementA)
		{

		}
	}
	class ConcreteVisitor2 : Visitor
	{
		public override void VisitElementA(ConcreteElementA elementA)
		{

		}
		public override void VisitElementB(ConcreteElementB elementA)
		{

		}
	}
	class ObjectStructure
	{
		private List<Element> elements = new List<Element>();
		public void Attach(Element element)
		{
			elements.Add(element);
		}
		public void Detach(Element element)
		{
			elements.Remove(element);
		}
		public void Accept(Visitor visitor)
		{
			foreach (Element e in elements)
			{
				e.Accept(visitor);
			}
		}
	}
	public static class VisitortMain
	{
		public static void Init()
		{
			ObjectStructure o = new ObjectStructure();
			o.Attach(new ConcreteElementA());
			o.Attach(new ConcreteElementB());

			ConcreteVisitor1 v1 = new ConcreteVisitor1();
			ConcreteVisitor2 v2 = new ConcreteVisitor2();

			o.Accept(v1);
			o.Accept(v2);

		}

	}
}
/*访问者模式：把处理从数据结构中分离出来。适用于稳定的数据结构和易于变化的算法，使算法操作的增加变得容易
 */
