
	//#--------------------------------------------------------------------------
		if(strlen(SLOT[SLOT_INDEX].MEDIATOR.DATA[0]) > 0){
			sprintf(IN_0,"%s",SLOT[SLOT_INDEX].MEDIATOR.DATA[0]);
		} else sprintf(IN_0,"0");

		if(strlen(SLOT[SLOT_INDEX].MEDIATOR.DATA[1]) > 0){
			sprintf(IN_1,"%s",SLOT[SLOT_INDEX].MEDIATOR.DATA[1]);
		} else sprintf(IN_1,"0");

		if(strlen(SLOT[SLOT_INDEX].MEDIATOR.DATA[2]) > 0){
			sprintf(IN_2,"%s",SLOT[SLOT_INDEX].MEDIATOR.DATA[2]);
		} else sprintf(IN_2,"0");

		if(strlen(SLOT[SLOT_INDEX].MEDIATOR.DATA[3]) > 0){
			sprintf(IN_3,"%s",SLOT[SLOT_INDEX].MEDIATOR.DATA[3]);
		} else sprintf(IN_3,"0");
	//#--------------------------------------------------------------------------
		sprintf(IN_0_NEW,"%ld",SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[0]);
		sprintf(IN_1_NEW,"%ld",SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[1]);
		sprintf(IN_2_NEW,"%ld",SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[2]);
		sprintf(IN_3_NEW,"%ld",SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[3]);
	//#--------------------------------------------------------------------------
		is_error = 0;
	//#------------------------------------------------------------------------
		PyEval_AcquireThread( pThreadState ) ;
		PyObject *PyObj;
	//#------------------------------------------------------------------------
		PyObj = PyString_FromString(IN_0);PyDict_SetItemString(Local_Dir, "IN_0", PyObj);
		PyObj = PyString_FromString(IN_1);PyDict_SetItemString(Local_Dir, "IN_1", PyObj);
		PyObj = PyString_FromString(IN_2);PyDict_SetItemString(Local_Dir, "IN_2", PyObj);
		PyObj = PyString_FromString(IN_3);PyDict_SetItemString(Local_Dir, "IN_3", PyObj);
	//#------------------------------------------------------------------------
		PyObj = PyString_FromString(IN_0_NEW);PyDict_SetItemString(Local_Dir, "IN_0_NEW", PyObj);
		PyObj = PyString_FromString(IN_1_NEW);PyDict_SetItemString(Local_Dir, "IN_1_NEW", PyObj);
		PyObj = PyString_FromString(IN_2_NEW);PyDict_SetItemString(Local_Dir, "IN_2_NEW", PyObj);
		PyObj = PyString_FromString(IN_3_NEW);PyDict_SetItemString(Local_Dir, "IN_3_NEW", PyObj);
	//#------------------------------------------------------------------------
		PyObj = PyString_FromString(MEM_0);
		PyDict_SetItemString(Local_Dir, "MEM_0", PyObj);
	//#------------------------------------------------------------------------
		PyObj = PyString_FromString("");
		for (i = 0; i < OUTPUT_LEN; i++){
			sprintf(OUT_NAME,"OUT_%d",i);
			PyDict_SetItemString(Local_Dir, OUT_NAME, PyObj);
		}
	//#------------------------------------------------------------------------
	//#	RUN PYTHON
	//#------------------------------------------------------------------------
		if (CODE_LEN > 0){

			pVal =  PyRun_String(Python_CODE, Py_file_input, Global_Dir, Local_Dir);

		} else {
			pVal =  PyRun_String(
			"#{\"PERIOD\":\"1\"} \n"
			"MEM_0 = "" \n"
			"OUT_0 = str(IN_0) \n"
		,Py_file_input, Global_Dir, Local_Dir);
		}
	//#------------------------------------------------------------------------
	//#	PYTHON ERROR
	//#------------------------------------------------------------------------

		if ( pVal != NULL )
			usleep(100);
			//assert( false ) ; // eek! it should've failed
		else
		{
			is_error = 1;
			PyObject *pExcType;
			PyObject *pExcValue;
			PyObject *pExcTraceback;
			PyObject *pRepr;


			PyErr_Fetch( &pExcType , &pExcValue , &pExcTraceback ) ;
			//if ( pExcType != NULL )
			//{
			//	PyObject* pRepr = PyObject_Repr( pExcType ) ;
			//	Py_DecRef( pRepr ) ;
			//	Py_DecRef( pExcType ) ;
			//}
			if ( pExcValue != NULL )
			{
					pRepr = PyObject_Repr( pExcValue ) ;
					sprintf(Error_value,"%s", PyString_AsString(pRepr));
					//printf("+ EXC value: %s\r\n",Error_value);
				//#-------------------------------------------------------------
					if((-1) == Python_parser_1 (Error_value, b64_Error_value)){
						Python_parser_2 (Error_value, b64_Error_value);
					}
				//#-------------------------------------------------------------
					sprintf(Error_value,"Python, %s", b64_Error_value);
					printf("- EXC value: %s\r\n",Error_value);//!!!!!
					_b64_encode(Error_value, b64_Error_value);
				//#-------------------------------------------------------------
					//Py_DecRef( pRepr ) ;
					//Py_DecRef( pExcValue ) ;
			}
			//if ( pExcTraceback != NULL )
			//{
			//	PyObject* pRepr = PyObject_Repr( pExcValue ) ;
			//	Py_DecRef( pRepr ) ;
			//	Py_DecRef( pExcTraceback ) ;
			//}


			Py_DecRef( pExcType );
			Py_DecRef( pExcValue );
			Py_DecRef( pExcTraceback );
			Py_DecRef( pRepr );

		}
	//#------------------------------------------------------------------------
	//#
	//#------------------------------------------------------------------------
		if(is_error == 0){

			PyObj = PyDict_GetItemString(Local_Dir, "MEM_0");
			sprintf(MEM_0,"%s",PyString_AsString(PyObj));
		//#------------------------------------------------------------------------
			PyObj = PyDict_GetItemString(Local_Dir, "IN_0_NEW");
			if ( PyObj != NULL ){
				if( PyString_Check(PyObj) == 1 ){
					sprintf(IN_0_NEW,"%s",PyString_AsString(PyObj));
					if(IN_0_NEW[0]=='0') SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[0] = 0;
				}
			}
			PyObj = PyDict_GetItemString(Local_Dir, "IN_1_NEW");
			if ( PyObj != NULL ){
				if( PyString_Check(PyObj) == 1 ){
					sprintf(IN_1_NEW,"%s",PyString_AsString(PyObj));
					if(IN_1_NEW[0]=='0') SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[1] = 0;
				}
			}
			PyObj = PyDict_GetItemString(Local_Dir, "IN_2_NEW");
			if ( PyObj != NULL ){
				if( PyString_Check(PyObj) == 1 ){
					sprintf(IN_2_NEW,"%s",PyString_AsString(PyObj));
					if(IN_2_NEW[0]=='0') SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[2] = 0;
				}
			}
			PyObj = PyDict_GetItemString(Local_Dir, "IN_3_NEW");
			if ( PyObj != NULL ){
				if( PyString_Check(PyObj) == 1 ){
					sprintf(IN_3_NEW,"%s",PyString_AsString(PyObj));
					if(IN_3_NEW[0]=='0') SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[3] = 0;
				}
			}
		//#------------------------------------------------------------------------
			for (i = 0; i < OUTPUT_LEN; i++){
				sprintf(OUT_NAME,"OUT_%d",i);
				PyObj = PyDict_GetItemString(Local_Dir, OUT_NAME);
				if ( PyObj != NULL ){
					if( PyString_Check(PyObj) == 1 ){
						OUT[0]=0;
						sprintf(OUT,"%s",PyString_AsString(PyObj));
						OUT_Len = strlen(OUT);
						if( OUT_Len > 0 )
						{
							if( OUT_Len <= DE_OUT_MAX_Length ){
							//#------------------------------------------------
							//# SAVE LAST ME DATA
							//#------------------------------------------------
								SYS_API__PUT__LAST_OUTPUT_DATA_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)i, OUT);
							//#-IOT STUDIO -----------------------------------------------
								sprintf(MyMessege,"{\"C\":\"0\",\"D\":\"%ld\",\"S\":\"%d\",\"V\":\"%s\"}",DEVICE_NAME,i,OUT);
								SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX,MyMessege);
							//#--------------------------------------------------------------------------
								pthread_mutex_lock( &SLOT[SLOT_INDEX].Device_cond_mutex );
								pthread_cond_broadcast( &SLOT[SLOT_INDEX].Device_condition );
								pthread_mutex_unlock( &SLOT[SLOT_INDEX].Device_cond_mutex );
							//#--------------------------------------------------------------------------
								usleep(DE_OUT_Delay);
							} else {
								sprintf(Error_value,"Python, OUT_%d string length(%ld) is too large (MAX=%d)",i,OUT_Len,DE_OUT_MAX_Length);
								_b64_encode(Error_value, b64_Error_value);
								is_error = 1;
							}
						}
					} else {
						sprintf(Error_value,"Python, OUT_%d is not a string",i);
						_b64_encode(Error_value, b64_Error_value);
						is_error = 1;
					}
				}
			}
		}
	//#------------------------------------------------------------------------
		Py_DecRef(PyObj);
		PyEval_ReleaseThread( pThreadState ) ;
	//#------------------------------------------------------------------------

	if(is_error == 1){

		//#--------------------------------------------------------------------------
			//printf("\r\n is_error Python_CODE \r\n");
			//printf("%s",Python_CODE);
			//printf("\r\n is_error Python_CODE \r\n");
			//printf("\r\n is_error >> DATA_NEW \r\n");
			SYS_API__PUT__DEVICE_DATA_STATUS_By_SLOT_INDEX(SLOT_INDEX, DATA_NEW);
			//printf("\r\n is_error Python_CODE \r\n");
		//#--------------------------------------------------------------------------



			sprintf(MyMessege,"{\"C\":\"2\",\"D\":\"%ld\",\"S\":\"0\",\"T\":\"1\",\"V\":\"%s\"}",DEVICE_NAME,b64_Error_value);
			//SYS_API__PUT__MESSEGE(SLOT_INDEX,MyMessege);
			SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX,MyMessege);
		//#--------------------------------------------------------------------------
			pthread_mutex_lock( &SLOT[SLOT_INDEX].Device_cond_mutex );
			pthread_cond_broadcast( &SLOT[SLOT_INDEX].Device_condition );
			pthread_mutex_unlock( &SLOT[SLOT_INDEX].Device_cond_mutex );
	}


