package negocio;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Contrato{

	private String puesto;
	private Integer salario;
	private List<Empresa> contratador;
	private List<Persona> empleado;

	// General constraints
	//if 'a' > 'b' then true else false endif
	//if self.puesto = 'Director' then forAll(c:Contrato|ifc.puesto='Director'thentrueelseself.salario>c.salarioendif) else true endif

	public Contrato(String puesto, Integer salario) {
		this.setPuesto(puesto);
		this.setSalario(salario);
		this.contratador = new ArrayList<Empresa>();
		this.empleado = new ArrayList<Persona>();
	}

	public String getPuesto() {
		return this.puesto;
	}

	public void setPuesto(String puesto) {
		//self.puesto = 'Trabajador' or self.puesto = 'Gerente' or self.puesto = 'Director'
		this.puesto = puesto;
	}

	public Integer getSalario() {
		return this.salario;
	}

	public void setSalario(Integer salario) {
				this.salario = salario;
	}

	public List<Empresa> getContratador() {
		return Collections.unmodifiableList(this.contratador);
	}

	public void addContratador(Empresa element) {
		this.contratador.add(element);
		element.addContrato(this);
	}

	public void removeContratador(Empresa element) {
		this.contratador.remove(element);
		element.removeContrato(this);
;
	}

	public List<Persona> getEmpleado() {
		return Collections.unmodifiableList(this.empleado);
	}

	public void addEmpleado(Persona element) {
		this.empleado.add(element);
		element.setContrato(this);
	}

	public void removeEmpleado(Persona element) {
		this.empleado.remove(element);
		element.setContrato(null);
	}

}
