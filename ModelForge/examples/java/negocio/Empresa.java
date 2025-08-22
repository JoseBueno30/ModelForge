package negocio;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Empresa{

	private String correo;
	private String dir;
	private String nombre;
	private Integer tlf;
	private Integer valor_minimo_pedido;
	private List<Contrato> contrato;
	private List<Etiqueta> etiqueta;

	public Empresa(String correo, String dir, String nombre, Integer tlf, Integer valor_minimo_pedido) {
		this.setCorreo(correo);
		this.setDir(dir);
		this.setNombre(nombre);
		this.setTlf(tlf);
		this.setValor_minimo_pedido(valor_minimo_pedido);
		this.contrato = new ArrayList<Contrato>();
		this.etiqueta = new ArrayList<Etiqueta>();
	}

	public String getCorreo() {
		return this.correo;
	}

	public void setCorreo(String correo) {
				this.correo = correo;
	}

	public String getDir() {
		return this.dir;
	}

	public void setDir(String dir) {
				this.dir = dir;
	}

	public String getNombre() {
		return this.nombre;
	}

	public void setNombre(String nombre) {
				this.nombre = nombre;
	}

	public Integer getTlf() {
		return this.tlf;
	}

	public void setTlf(Integer tlf) {
				this.tlf = tlf;
	}

	public Integer getValor_minimo_pedido() {
		return this.valor_minimo_pedido;
	}

	public void setValor_minimo_pedido(Integer valor_minimo_pedido) {
				this.valor_minimo_pedido = valor_minimo_pedido;
	}

	public List<Contrato> getContrato() {
		return Collections.unmodifiableList(this.contrato);
	}

	public void addContrato(Contrato element) {
		this.contrato.add(element);
	}

	public void removeContrato(Contrato element) {
		this.contrato.remove(element);
	}

	public List<Etiqueta> getEtiqueta() {
		return Collections.unmodifiableList(this.etiqueta);
	}

	public void addEtiqueta(Etiqueta element) {
		this.etiqueta.add(element);
	}

	public void removeEtiqueta(Etiqueta element) {
		this.etiqueta.remove(element);
	}

}
