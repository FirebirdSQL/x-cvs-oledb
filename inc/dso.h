/*
 * Firebird Open Source OLE DB driver
 *
 * DSO.H - Include file for OLE DB Data SOurce Object object definition.
 *
 * Distributable under LGPL license.
 * You may obtain a copy of the License at http://www.gnu.org/copyleft/lgpl.html
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * LGPL License for more details.
 *
 * This file was created by Ralph Curry.
 * All individual contributions remain the Copyright (C) of those
 * individuals. Contributors to this file are either listed here or
 * can be obtained from a CVS history command.
 *
 * All rights reserved.
 */

#ifndef _IBOLEDB_DSO_H_
#define _IBOLEDB_DSO_H_

#include "resource.h"

#define DSF_UNINITIALIZED	0
#define DSF_INITIALIZED		1

class CInterBaseDSO:
	public CComObjectRoot,
	public CComCoClass<CInterBaseDSO, &CLSID_InterBaseProvider>,
	public IDBCreateSession,
	public IDBInitialize,
	public IDBInfo,
	public IDBProperties,
	public IPersist,
	public ISupportErrorInfo
{
public:
	CInterBaseDSO();
	~CInterBaseDSO();

	DECLARE_REGISTRY(CLSID_InterBaseProvider, PROGID_InterBaseProvider_Version, PROGID_InterBaseProvider, IDS_InterBaseProviderDSO, THREADFLAGS_BOTH)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	/* The ATL interface map */
	BEGIN_COM_MAP(CInterBaseDSO)
		COM_INTERFACE_ENTRY(IDBCreateSession)
		COM_INTERFACE_ENTRY(IDBInitialize)
		COM_INTERFACE_ENTRY(IDBInfo)
		COM_INTERFACE_ENTRY(IDBProperties)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_POLY_AGGREGATABLE(CInterBaseDSO)

	HRESULT DeleteSession(void);

/* IDBCreateSession */
	virtual HRESULT STDMETHODCALLTYPE CreateSession( 
		IUnknown  *pUnkOuter,
		REFIID     riid,
		IUnknown **ppDBSession);

/* IDBInitialize */
	virtual HRESULT STDMETHODCALLTYPE Initialize(void);        
	virtual HRESULT STDMETHODCALLTYPE Uninitialize(void);

/* IDBInfo */
	virtual HRESULT STDMETHODCALLTYPE GetKeywords(LPOLESTR *);
	virtual HRESULT STDMETHODCALLTYPE GetLiteralInfo(
		ULONG             cLiterals,
		const DBLITERAL   rgLiterals[],
		ULONG            *pcLiteralInfo,
		DBLITERALINFO   **prgLiteralInfo,
		OLECHAR         **ppCharBuffer);

/* IDBProperties */
	virtual HRESULT STDMETHODCALLTYPE GetProperties( 
		ULONG               cPropertyIDSets,
		const DBPROPIDSET   rgPropertyIDSets[],
		ULONG              *pcPropertySets,
		DBPROPSET         **prgPropertySets);
        
	virtual HRESULT STDMETHODCALLTYPE GetPropertyInfo( 
		ULONG               cPropertyIDSets,
		const DBPROPIDSET   rgPropertyIDSets[],
		ULONG              *pcPropertyInfoSets,
		DBPROPINFOSET     **prgPropertyInfoSets,
		OLECHAR           **ppDescBuffer);
	    
	virtual HRESULT STDMETHODCALLTYPE SetProperties( 
		ULONG       cPropertySets,
		DBPROPSET   rgPropertySets[]);

/* IPersist */
	STDMETHODIMP GetClassID(
		CLSID  *pClassID);

/* ISupportErrorInfo */
	STDMETHODIMP InterfaceSupportsErrorInfo(
		REFIID   iid);

private:
	CInterBaseError   *m_pInterBaseError;
	char              *m_szDatabase;
	char              *m_pchDPB;
	DWORD              m_dwStatus;
	ULONG              m_cOpenSessions;
	short              m_cbDPB;

	CRITICAL_SECTION   m_cs;

	isc_db_handle      m_iscDbHandle;

	HRESULT BeginMethod(
		REFIID   riid);

	HRESULT WINAPI InternalQueryInterface(
		CInterBaseDSO            *pThis,
		const _ATL_INTMAP_ENTRY  *pEntries, 
		REFIID                    iid, 
		void                    **ppvObject);

#define FIRST_INIT_PROPERTY DBPROP_INIT_LOCATION
#define INIT_LOCATION_INDEX         0
#define INIT_DATASOURCE_INDEX       1
#define AUTH_USERID_INDEX           2
#define AUTH_PASSWORD_INDEX         3
#define INIT_PROVIDERSTRING_INDEX   4
#define INIT_PROMPT_INDEX           5
#define INIT_HWND_INDEX             6

BEGIN_IBPROPERTY_MAP
	BEGIN_IBPROPERTY_SET(DBPROPSET_DATASOURCE)
		IBPROPERTY_INFO_ENTRY_RO(CURRENTCATALOG, (DWORD)0)
	END_IBPROPERTY_SET(DBPROPSET_DATASOURCE)
	BEGIN_IBPROPERTY_SET(DBPROPSET_DATASOURCEINFO)
		IBPROPERTY_INFO_ENTRY_RO(ACTIVESESSIONS, (DWORD)0)
		IBPROPERTY_INFO_ENTRY_RO(BYREFACCESSORS, VARIANT_FALSE)
		IBPROPERTY_INFO_ENTRY_RO(CATALOGUSAGE, (DWORD)0)
		IBPROPERTY_INFO_ENTRY_RO(CONCATNULLBEHAVIOR, (DWORD)DBPROPVAL_CB_NULL)
		IBPROPERTY_INFO_ENTRY_RO(DATASOURCEREADONLY, VARIANT_FALSE)
		IBPROPERTY_INFO_ENTRY_RO(DBMSNAME, L"InterBase Server")
		IBPROPERTY_INFO_ENTRY_RO(DSOTHREADMODEL,  (DWORD)(DBPROPVAL_RT_FREETHREAD | DBPROPVAL_RT_SINGLETHREAD))
		IBPROPERTY_INFO_ENTRY_RO(IDENTIFIERCASE,  (DWORD)DBPROPVAL_IC_UPPER)
		IBPROPERTY_INFO_ENTRY_RO(MULTIPLERESULTS, (DWORD)0)
		IBPROPERTY_INFO_ENTRY_RO(MULTIPLESTORAGEOBJECTS, VARIANT_TRUE)
		IBPROPERTY_INFO_ENTRY_RO(NULLCOLLATION, (DWORD)DBPROPVAL_NC_END)
		IBPROPERTY_INFO_ENTRY_RO(OLEOBJECTS,    (DWORD)DBPROPVAL_OO_BLOB)
		IBPROPERTY_INFO_ENTRY_RO(OUTPUTPARAMETERAVAILABILITY, (DWORD)DBPROPVAL_OA_ATEXECUTE)
		IBPROPERTY_INFO_ENTRY_RO(PROVIDERNAME, PROVIDER_NAME)
		IBPROPERTY_INFO_ENTRY_RO(PROVIDEROLEDBVER, LPOLESTR(L"02.00"))
		IBPROPERTY_INFO_ENTRY_RO(PROVIDERVER, LPOLESTR(L"02.00.0206"))
		IBPROPERTY_INFO_ENTRY_RO(PROCEDURETERM, LPOLESTR(L"stored procedure"))
		IBPROPERTY_INFO_ENTRY_RO(PROVIDERFRIENDLYNAME, LPOLESTR(L"OLE DB Provider for InterBase"))
		IBPROPERTY_INFO_ENTRY_RO(QUOTEDIDENTIFIERCASE,  (DWORD)DBPROPVAL_IC_SENSITIVE)
		IBPROPERTY_INFO_ENTRY_RO(SQLSUPPORT, (DWORD)DBPROPVAL_SQL_ANSI92_ENTRY)
		IBPROPERTY_INFO_ENTRY_RO(STRUCTUREDSTORAGE, (DWORD)(DBPROPVAL_SS_ISEQUENTIALSTREAM))
		IBPROPERTY_INFO_ENTRY_RO(SUPPORTEDTXNISOLEVELS, (DWORD)(DBPROPVAL_TI_READCOMMITTED | DBPROPVAL_TI_REPEATABLEREAD | DBPROPVAL_TI_SERIALIZABLE))
		IBPROPERTY_INFO_ENTRY_RO(TABLETERM, LPOLESTR(L"table"))
	END_IBPROPERTY_SET(DBPROPSET_DATASOURCEINFO)
	BEGIN_IBPROPERTY_SET(DBPROPSET_DBINIT)
		IBPROPERTY_INFO_ENTRY_RW(INIT_LOCATION, LPOLESTR(L""))
		IBPROPERTY_INFO_ENTRY_RW(INIT_DATASOURCE, LPOLESTR(L""))
		IBPROPERTY_INFO_ENTRY_RW(AUTH_USERID, LPOLESTR(L""))
		IBPROPERTY_INFO_ENTRY_RW(AUTH_PASSWORD, LPOLESTR(L""))
		IBPROPERTY_INFO_ENTRY_RW(INIT_PROVIDERSTRING, LPOLESTR(L""))
		IBPROPERTY_INFO_ENTRY_RW(INIT_PROMPT, (DWORD)DBPROMPT_NOPROMPT)
		IBPROPERTY_INFO_ENTRY_RW(INIT_HWND, (DWORD)0)
		IBPROPERTY_INFO_ENTRY_RW(AUTH_PERSIST_SENSITIVE_AUTHINFO, VARIANT_TRUE)
		IBPROPERTY_INFO_ENTRY_RW(INIT_TIMEOUT, (DWORD)0)
	END_IBPROPERTY_SET(DBPROPSET_DBINIT)
END_IBPROPERTY_MAP
};
#endif /* _IBOLEDB_DSO_H_ (not) */
