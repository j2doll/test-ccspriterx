
#include "cocos2d.h" 
using namespace cocos2d;

#include "CCSpriterX.h"


namespace SCMLHelper
{

	///////////////////////////////////////////////////////////////////////////////////

	File::File()
		: sprite(NULL)
	{
	}


	File::~File()
	{
		if (sprite)
			sprite->release();

	}

	void File::Init(TiXmlNode *node)
	{
		TiXmlElement *element = node->ToElement();
		if (element)
		{
			int intValue;
			float floatValue;

			if (element->QueryIntAttribute("id", &intValue) == TIXML_SUCCESS)
				id = intValue;
			else
				id = 0;

			name = element->Attribute("name");

			if (element->QueryFloatAttribute("width", &floatValue) == TIXML_SUCCESS)
				width = floatValue;
			else
				width = 0;

			if (element->QueryFloatAttribute("height", &floatValue) == TIXML_SUCCESS)
				height = floatValue;
			else
				height = 0;

			if (name.size()>0)
			{
				sprite = CCSprite::create(name.c_str());
				sprite->retain();
			}

		}

	}

	///////////////////////////////////////////////////////////////////////////////////

	Folder::Folder()
		: mId(0)
	{ 
		mFiles.reserve(50); 
	}


	Folder::~Folder()
	{
		int count = mFiles.size();
		for (int i=0;i<count;i++)
			CC_SAFE_DELETE(mFiles[i]);

		mFiles.clear();

	}


	int Folder::GetFileCount()
	{
		return mFiles.size();

	}

	
	File *Folder::GetFile(int index)
	{
		if (index < (int)mFiles.size())
			return mFiles[index];

		return NULL;

	}


	void Folder::Init(TiXmlNode *node)
	{
		TiXmlElement *element = node->ToElement();
		if (element)
		{
			int intValue;

			if (element->QueryIntAttribute("id", &intValue) == TIXML_SUCCESS)
				mId= intValue;


			mName = element->Attribute("name");

			for (TiXmlNode* fileNode = node->FirstChild(); fileNode; fileNode = fileNode->NextSibling())
			{
				File *file = new File();
				file->Init(fileNode);

				mFiles.push_back(file);
			}

		}

	}

	///////////////////////////////////////////////////////////////////////////////////

	void ObjectRef::Init(TiXmlNode *node)
	{
		TiXmlElement *element = node->ToElement();
		if (element)
		{
			int intValue;

			if (element->QueryIntAttribute("id", &intValue) == TIXML_SUCCESS)
				id = intValue;
			else
				id = 0;

			if (element->QueryIntAttribute("timeline", &intValue) == TIXML_SUCCESS)
				timeline = intValue;
			else
				timeline = 0;

			if (element->QueryIntAttribute("key", &intValue) == TIXML_SUCCESS)
				key = intValue;
			else
				key = 0;

			if (element->QueryIntAttribute("z_index", &intValue) == TIXML_SUCCESS)
				z_index = intValue;
			else
				z_index = 0;

		}
	}


	///////////////////////////////////////////////////////////////////////////////////

	void Object::Init(TiXmlNode *node, CCSpriterX *animator)
	{
		sprite = NULL;

        float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
        
		TiXmlElement *element = node->ToElement();
		if (element)
		{
			int intValue;
			float floatValue;

			if (element->QueryIntAttribute("folder", &intValue) == TIXML_SUCCESS)
				folder = intValue;
			else
				folder = 0;

			if (element->QueryIntAttribute("file", &intValue) == TIXML_SUCCESS)
				file = intValue;
			else
				file = 0;

			if (element->QueryFloatAttribute("x", &floatValue) == TIXML_SUCCESS)
				x = floatValue/scaleFactor;
			else
				x = 0;

			if (element->QueryFloatAttribute("y", &floatValue) == TIXML_SUCCESS)
				y = floatValue/scaleFactor;
			else
				y = 0;

			if (element->QueryFloatAttribute("angle", &floatValue) == TIXML_SUCCESS)
				angle = floatValue;
			else
				angle = 0;

			if (element->QueryFloatAttribute("pivot_x", &floatValue) == TIXML_SUCCESS)
				pivot_x = floatValue;
			else
				pivot_x = 0;

			if (element->QueryFloatAttribute("pivot_y", &floatValue) == TIXML_SUCCESS)
				pivot_y = floatValue;
			else
				pivot_y = 1;

			if (element->QueryIntAttribute("z_index", &intValue) == TIXML_SUCCESS)
				z_index = intValue;
			else
				z_index = 0;

			sprite = animator->getSprite(folder, file);

		}
	}


	///////////////////////////////////////////////////////////////////////////////////

	Key::Key()
		: mId(0)
		, mTime(0)
		, mSpinCounterClockwise(true)
	{ 
		mObjects.reserve(50);
		mObjectRefs.reserve(50); 
	}


	Key::~Key()
	{
		int count = mObjects.size();
		for (int i=0;i<count;i++)
			CC_SAFE_DELETE(mObjects[i]);

		mObjects.clear();

		count = mObjectRefs.size();
		for (int i=0;i<count;i++)
			CC_SAFE_DELETE(mObjectRefs[i]);

		mObjectRefs.clear();

	}


	int Key::GetObjectRefCount()
	{
		return mObjectRefs.size();

	}


	ObjectRef *Key::GetObjectRef(int index)
	{
		if (index < (int)mObjectRefs.size())
			return mObjectRefs[index];

		return NULL;

	}


	int Key::GetObjectCount()
	{
		return mObjects.size();

	}


	Object *Key::GetObject(int index)
	{
		if (index < (int)mObjects.size())
			return mObjects[index];

		return NULL;

	}


	float Key::GetTime()
	{
		return mTime;
	}


	bool Key::IsSpinCounterClockwise()
	{
		return mSpinCounterClockwise;

	}


	void Key::Init(TiXmlNode *node, CCSpriterX *animator)
	{
		TiXmlElement *element = node->ToElement();
		if (element)
		{
			int intValue;
			float floatValue;
			if (element->QueryIntAttribute("id", &intValue) == TIXML_SUCCESS)
				mId = intValue;

			float time = 0;
			if (element->QueryFloatAttribute("time", &floatValue) == TIXML_SUCCESS)		// was in milliseconds, convert to seconds instead
				time = floatValue/1000.0f;
			mTime = time;

			if (element->QueryIntAttribute("spin", &intValue) == TIXML_SUCCESS)
				mSpinCounterClockwise = !(intValue == -1);

			for (TiXmlNode* objNode = node->FirstChild(); objNode; objNode = objNode->NextSibling())
			{
				element = objNode->ToElement();
				const char *tabObj = element->Value();

				if (strcmp(tabObj, "object_ref")==0)
				{
					ObjectRef *ref = new ObjectRef();
					ref->Init(objNode);

					mObjectRefs.push_back(ref);

				}
				else if (strcmp(tabObj, "object")==0)
				{
					Object *obj = new Object();
					obj->Init(objNode, animator);

					mObjects.push_back(obj);
				}
			}
		}

	}


	///////////////////////////////////////////////////////////////////////////////////
	
	Timeline::Timeline()
		: mId(0)
	{
		mKeyframes.reserve(50);
	}


	Timeline::~Timeline()
	{
		int count = mKeyframes.size();
		for (int i=0;i<count;i++)
		{
			CC_SAFE_DELETE(mKeyframes[i]);

		}

	}


	int Timeline::GetKeyframeCount()
	{
		return mKeyframes.size();

	}


	Key *Timeline::GetKeyframe(int index)
	{
		if (index < (int)mKeyframes.size())
		{
			return mKeyframes[index];
		}

		return NULL;

	}

	void Timeline::Init(TiXmlNode *node, CCSpriterX *animator)
	{
		int intValue;

		TiXmlElement *element = node->ToElement();

		if (element)
		{
			if (element->QueryIntAttribute("id", &intValue) == TIXML_SUCCESS)
				mId = intValue;

			for (TiXmlNode* keyNode = node->FirstChild(); keyNode; keyNode = keyNode->NextSibling())
			{
				element = keyNode->ToElement();
				if (element)
				{
					Key *keyframe = new Key();

					keyframe->Init(keyNode, animator);

					mKeyframes.push_back(keyframe);
				}
			}

		}

	}

	///////////////////////////////////////////////////////////////////////////////////

	Animation::Animation()
		: mId(0)
		, mCurrKeyframe(0)
		, mMainline(NULL)
		, mDone(false)
		, mTimer(0)
	{
		mTimelines.reserve(50);

	}


	Animation::~Animation()
	{
		int count = mTimelines.size();
		for (int i=0;i<count;i++)
			CC_SAFE_DELETE(mTimelines[i]);

		mTimelines.clear();

	}


	void Animation::Init(TiXmlNode *node, CCSpriterX *animator)
	{
		int intValue;
		float floatValue;

		TiXmlElement *element = node->ToElement();

		if (element)
		{
			if (element->QueryIntAttribute("id", &intValue) == TIXML_SUCCESS)
				mId = intValue;

			mName = element->Attribute("name");

			if (element->QueryFloatAttribute("length", &floatValue) == TIXML_SUCCESS)
				mLength = floatValue/1000.0f;							// was in milliseconds, convert to seconds instead

			const char *looping = element->Attribute("looping");		// was set to "false" in alpha, but in fact looping all the time
			mLooping = true;

			for (TiXmlNode* lineNode = node->FirstChild(); lineNode; lineNode = lineNode->NextSibling())
			{
				element = lineNode->ToElement();

				const char *tabLine = element->Value();
				if (strcmp(tabLine, "mainline")==0)						// 1 mainline only
				{
					mMainline = new Timeline();
					mMainline->Init(lineNode, animator);

				}
				else if (strcmp(tabLine, "timeline")==0)
				{
					Timeline *timeline = new Timeline();
					timeline->Init(lineNode, animator);

					mTimelines.push_back(timeline);

				}

			}
		}

	}


	bool Animation::IsDone()
	{
		return mDone;

	}


	void Animation::Restart()
	{
		mDone = false;
		mTimer = 0;
		mCurrKeyframe = 0;

	}

	std::string Animation::GetName()
	{
		return this->mName; 
	}

	void Animation::Update(float dt)
	{

		mTimer += dt;
		if (mTimer >= mLength)
		{
			mDone = true;

			Restart();			// always looping for now

		}
        
		int count = mMainline->GetKeyframeCount();
		Key *keyframe = mMainline->GetKeyframe(mCurrKeyframe);
		float currTime = keyframe->GetTime();

		Key *keyframeNext = NULL;

		int next = mCurrKeyframe+1;

		if (next > count-1)		// looping
			next = 0;
	
		keyframeNext = mMainline->GetKeyframe(next);
		
		if (keyframeNext)
		{
			float nextTime = keyframeNext->GetTime();
			if (next == 0)
				nextTime = mLength;

			if (mTimer >= nextTime)
			{

				mCurrKeyframe = next;

				keyframe = keyframeNext;
				currTime = keyframe->GetTime();

				next = mCurrKeyframe+1;
				if (next > count-1)				// looping
					next = 0;
					
				keyframeNext = mMainline->GetKeyframe(next);
				if (keyframeNext == NULL)
					return;

				nextTime = keyframeNext->GetTime();
				if (next == 0)
					nextTime = mLength;
					
			}


			float t = (mTimer-currTime)/(nextTime-currTime);

			int count = keyframe->GetObjectRefCount();
			for (int i=0;i<count;i++)
			{
				ObjectRef *ref = keyframe->GetObjectRef(i);
			
				ObjectRef *refNext = keyframeNext->GetObjectRef(i);

				if (ref && refNext)
				{

					Key *keyRef = mTimelines[ref->timeline]->GetKeyframe(ref->key);
					Object *obj = keyRef->GetObject(0);									// should be only 1 object

					Key *keyRefNext = mTimelines[refNext->timeline]->GetKeyframe(refNext->key);
					Object *objNext = keyRefNext->GetObject(0);

					float x = obj->x+(objNext->x-obj->x)*t;
					float y = obj->y+(objNext->y-obj->y)*t;
					float angle = objNext->angle-obj->angle;
					if (keyRef->IsSpinCounterClockwise())
					{
						if (angle < 0)
							angle = (objNext->angle+360)-obj->angle;
					}
					else
					{
						if (angle > 0)
						{
							angle = (objNext->angle-360)-obj->angle;
						}

					}

					if (ref->timeline != refNext->timeline)	
						t = 0;

					angle = obj->angle+(angle)*t;

					if (angle >= 360)
						angle -= 360;

					float px = obj->pivot_x+(objNext->pivot_x-obj->pivot_x)*t;
					float py = obj->pivot_y+(objNext->pivot_y-obj->pivot_y)*t;

					CCPoint newPos = ccp(x, y);
					obj->sprite->setPosition(newPos);
					obj->sprite->setRotation(-angle);
					obj->sprite->setAnchorPoint(ccp(px, py));
						
				}
				

			}
		}
		

	}

	void Animation::Render()
	{
		Key *keyframe = mMainline->GetKeyframe(mCurrKeyframe);

		int count = keyframe->GetObjectRefCount();
		for (int i=0;i<count;i++)
		{
			ObjectRef *ref = keyframe->GetObjectRef(i);

			if (ref)
			{

				Key *keyRef = mTimelines[ref->timeline]->GetKeyframe(ref->key);
				Object *obj = keyRef->GetObject(0);									// should be only 1 object
				obj->sprite->visit();
						
			}

		}

	}


	///////////////////////////////////////////////////////////////////////////////////

	Entity::Entity()
		: mCurrAnimation(0)
		, mId(0)
	{
		mAnimations.reserve(50);
	};


	Entity::~Entity()
	{
		int count = mAnimations.size();
		for (int i=0;i<count;i++)
			CC_SAFE_DELETE(mAnimations[i]);

		mAnimations.clear();

	}


	void Entity::Update(float dt)
	{
		
		Animation *animation = mAnimations[mCurrAnimation];
		animation->Update(dt);

	}


	void Entity::Render()
	{
		Animation *animation = mAnimations[mCurrAnimation];
		animation->Render();

	}


	void Entity::NextAnimation()
	{
		mCurrAnimation++;
		if (mCurrAnimation >= (int)mAnimations.size())
			mCurrAnimation = 0;

		Animation *animation = mAnimations[mCurrAnimation];
		animation->Restart();
	}

	bool Entity::SetCurrentAnimationIndex(unsigned int animationIndex)
	{
		if ( animationIndex >= (unsigned int)mAnimations.size() )
			return false; 

		Animation* animation = mAnimations[animationIndex];
		if ( NULL == animation )
			return false;

		mCurrAnimation = animationIndex; 
		animation->Restart(); 
		return true; 
	}

	bool Entity::SetCurrentAnimationName(std::string animationName, int& animationIndex)
	{
		if ( animationName.empty() )
			return false;

		animationIndex = -1;
		for ( std::vector<Animation *>::iterator _it = mAnimations.begin();
			  _it != mAnimations.end() ;
			  _it++ )
		{
			animationIndex++;

			Animation* animation = (*_it);
			if ( animation == NULL )
				continue; 

			if ( animation->GetName() == animationName )
			{
				mCurrAnimation = animationIndex; 

				Animation* curAni = mAnimations[ mCurrAnimation ];
				curAni->Restart();   

				return true;  
			}
		}

		animationIndex = -1;
		return false; 
	}
	
	void Entity::SetId(int id)
	{
		mId = id;

	}


	void Entity::SetName(const char *name)
	{
		mName = name;
	}

	std::string Entity::GetName()
	{
		return mName;
	}


	void Entity::AddAnimation(Animation *animation)
	{
		mAnimations.push_back(animation);

	}

}

///////////////////////////////////////////////////////////////////////////////////

using namespace SCMLHelper;

CCSpriterX::CCSpriterX(unsigned int maxFolderSize, unsigned int maxEntitySize)
	: cocos2d::CCNode() 
{
	mFolders.reserve( maxFolderSize );
	mEntities.reserve( maxEntitySize );

	mCurrEntity = 0; 
}


CCSpriterX::~CCSpriterX()
{
}


CCSpriterX* CCSpriterX::create(const char *filename, unsigned int maxFolderSize, unsigned int maxEntitySize)
{
	CCSpriterX *animator = new CCSpriterX(maxFolderSize, maxEntitySize);
	if (animator && animator->initWithFile(filename))
	{
		animator->autorelease();
		return animator;
	}

	CC_SAFE_DELETE(animator);
	return NULL;
}


void CCSpriterX::update(float dt)
{
	if (dt > 0.0167f)
		dt = 0.0167f;

	Entity *entity = mEntities[mCurrEntity];
	entity->Update(dt);

}


void CCSpriterX::draw(void)
{
	Entity *entity = mEntities[mCurrEntity];
	entity->Render();

}

bool CCSpriterX::setCurrentAnimation( unsigned int animationId )
{
	SCMLHelper::Entity* entity = mEntities[ mCurrEntity ];
	if ( NULL == entity )
		return false;
	
	if ( ! entity->SetCurrentAnimationIndex( animationId ) )
		return false;

	return true; 
}

bool CCSpriterX::setCurrentAnimation(std::string animationName)
{
	SCMLHelper::Entity* entity = mEntities[ mCurrEntity ];
	if ( NULL == entity )
		return false;

	int animationIndex = -1;
	if ( ! entity->SetCurrentAnimationName( animationName, animationIndex ) )
		return false;

	return true; 
}

 unsigned int CCSpriterX::getCurrentEntityIndex()
 {
	 return this->mCurrEntity;
 }

CCSprite *CCSpriterX::getSprite(unsigned int folderId, unsigned int fileId)
{
	if (folderId < (unsigned int)mFolders.size())
	{
		Folder *folder = mFolders[folderId]; 
		if (folder)
		{
			File *file = folder->GetFile(fileId);
			if (file)
				return file->sprite;
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
//
bool CCSpriterX::initWithFile(const char *filename)
{
	if ( filename == NULL )
		return false;

	const char* path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(filename);
	if ( path == NULL )
		return false;

	unsigned long filesize = 0; 
	char* buffer = (char *) CCFileUtils::sharedFileUtils()->getFileData(path, "rb", &filesize);
	if ( buffer == NULL )
		return false;

	mCurrEntity = 0;

	TiXmlDocument doc;

	doc.Parse(buffer);

	TiXmlNode *root = doc.FirstChild("spriter_data"); 
	if (root)
	{
		
		TiXmlElement *element = root->ToElement();

		const char *version = element->Attribute("scml_version");
		const char *generator = element->Attribute("generator");
		const char *generatorVersion = element->Attribute("generator_version");

			

		for (TiXmlNode* entityNode = root->FirstChild(); entityNode; entityNode = entityNode->NextSibling())
		{
			element = entityNode->ToElement();

			if (element)
			{
				const char *tab = element->Value();

				if (strcmp(tab, "folder")==0)
				{
					Folder *folder = new Folder();

					folder->Init(entityNode);

					mFolders.push_back(folder);

				}
				else if (strcmp(tab, "entity")==0)
				{
					int intValue;
					Entity *entity = new Entity();

					if (element->QueryIntAttribute("id", &intValue) == TIXML_SUCCESS)
						entity->SetId(intValue);

					entity->SetName(element->Attribute("name"));

					for (TiXmlNode* animationNode = entityNode->FirstChild(); animationNode; animationNode = animationNode->NextSibling())
					{
						Animation *animation = new Animation();
						animation->Init(animationNode, this);

						entity->AddAnimation(animation);

					}

					mEntities.push_back(entity);

				}

			}

		}

	}

	CC_SAFE_DELETE_ARRAY(buffer);

	this->scheduleUpdate();

	return true;

}
	

