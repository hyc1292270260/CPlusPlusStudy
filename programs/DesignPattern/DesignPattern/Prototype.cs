using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
	abstract class Prototype
	{
		public string Id { get; private set; }
		public abstract Prototype Clone();

	}
	class ConcretePrototype1 : Prototype
	{
		public ConcretePrototype1(string id)
		{

		}
		public override Prototype Clone()
		{
			return (Prototype)MemberwiseClone();
		}
	}
	public static class PrototypeMain
	{
		public static void Init()
		{
			ConcretePrototype1 a = new ConcretePrototype1("1");
			ConcretePrototype1 b = (ConcretePrototype1)a.Clone();

			Resume x = new Resume("a");
			x.SetInfo("男", "20");
			x.SetWorkExperience("1998", "XX公司");

			Resume y = (Resume)x.Clone();
			y.SetWorkExperience("1999", "YY公司");

			Resume z = (Resume)x.Clone();
			z.SetWorkExperience("2020", "ZZ公司");

		}

	}
	class WorkExperience : ICloneable
	{
		public string WorkDate { get;  set; }
		public string Company{ get;  set; }
		public Object Clone()
		{
			return (Object)this.MemberwiseClone();
		}
	}
	class Resume : ICloneable
	{
		private string name;
		private string age;
		private string sex;
		private WorkExperience workExperience;
		public Resume(string name)
		{
			this.name = name;
			workExperience = new WorkExperience();
		}
		private Resume(WorkExperience work)
		{
			this.workExperience = (WorkExperience)work.Clone();
		}
		public void SetInfo(string age, string sex)
		{
			this.age = age;
			this.sex = sex;
		}
		public void SetWorkExperience(string workDate, string company)
		{
			workExperience.WorkDate = workDate;
			workExperience.Company = company;
		}
		public Object Clone()
		{
			Resume obj = new Resume(this.workExperience);
			obj.name = this.name;
			obj.sex = this.sex;
			obj.age = this.age;
			return (Object)this.MemberwiseClone();
		}
	}
}
/*原型模式：初始化信息不变的情况下，克隆可以隐藏创建的细节，还能提高性能； .Net提供了ICloneable接口，唯一一个方法clone()
 * 外观模式：客户端调用外观类，外观类内部由多种组合方法供外部调用
 * 模板方法模式：模板、多态：通用行为放在父类，子类代码去重
 * 
 */
