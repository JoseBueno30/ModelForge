package bankaccount;

public abstract class SuperAccount{

	private Integer attribute1;

	public SuperAccount(Integer attribute1) {
		this.setAttribute1(attribute1);
	}

	public Integer getAttribute1() {
		return this.attribute1;
	}

	public void setAttribute1(Integer attribute1) {
				this.attribute1 = attribute1;
	}

}
