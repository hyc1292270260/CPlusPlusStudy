using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
    abstract class PersonBuilder
    {
		public abstract void BuildHead();
		public abstract void BuildBody();
		public abstract void BuildLeg();
		public abstract void BuildArm();
	}
	class PersonBuider1 : PersonBuilder
	{
		public override void BuildHead()
		{
			
		}
		public override void BuildBody()
		{
			
		}
		public override void BuildLeg()
		{
		}
		public override void BuildArm()
		{
			
		}
	
	}
	class PersonBuider2 : PersonBuilder
	{
		public override void BuildHead()
		{

		}
		public override void BuildBody()
		{

		}
		public override void BuildLeg()
		{
		}
		public override void BuildArm()
		{

		}

	}
	class PersonDirector
	{
		private PersonBuilder pb;
		public PersonDirector(PersonBuilder pb)
		{
			this.pb = pb;
		}
		public void CreatePerson()
		{
			pb.BuildHead();
			pb.BuildBody();
			pb.BuildArm();
			pb.BuildLeg();
		}
	}
	public static class BuilderpeMain
	{
		public static void Init()
		{
			PersonDirector pd1= new PersonDirector(new PersonBuider1());
			pd1.CreatePerson();

			PersonDirector pd2 = new PersonDirector(new PersonBuider2());
			pd2.CreatePerson();
		}

	}
}
/*建造者模式：创建一些步骤复杂的对象，这些对象内部件早顺序稳定
 */
